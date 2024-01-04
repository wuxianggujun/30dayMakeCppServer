//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Server.hpp"
#include "Socket.hpp"
#include "Acceptor.hpp"
#include "Connection.hpp"
#include "ThreadPool.hpp"
#include "EventLoop.hpp"
#include "util.hpp"
#include <unistd.h>
#include <functional>

Server::Server(EventLoop *loop) : main_Reactor_(loop), acceptor_(nullptr), thread_Pool_(nullptr) {
    acceptor_ = new Acceptor(main_Reactor_);
    std::function<void(Socket *)> cb = [this](auto && PH1) { NewConnection(std::forward<decltype(PH1)>(PH1)); };
    acceptor_->SetNewConnectionCallback(cb);

    int size = static_cast<int>(std::thread::hardware_concurrency());
    thread_Pool_ = new ThreadPool(size);
    for (int i = 0; i < size; ++i) {
        sub_Reactor_.push_back(new EventLoop());
    }

    for (int i = 0; i < size; ++i) {
        std::function<void()> sub_loop = std::bind(&EventLoop::Loop, sub_Reactor_[i]);
        thread_Pool_->Add(std::move(sub_loop));
    }
}

Server::~Server() {
    delete acceptor_;
    delete thread_Pool_;
}

void Server::NewConnection(Socket *sock) {
    ErrorIf(sock->GetFd() == -1, "new connection error");
    uint64_t random = sock->GetFd() % sub_Reactor_.size();
    auto *conn = new Connection(sub_Reactor_[random], sock);
    std::function<void(Socket *)> cb = [this](auto && PH1) { DeleteConnection(std::forward<decltype(PH1)>(PH1)); };
    conn->SetDeleteConnectionCallback(cb);
    conn->SetOnConnectCallback(on_connect_callback_);
    connections_[sock->GetFd()] = conn;
}

void Server::DeleteConnection(Socket *sock) {
    int sockfd = sock->GetFd();
    auto it = connections_.find(sockfd);
    if (it != connections_.end()) {
        Connection *conn = connections_[sockfd];
        connections_.erase(sockfd);
        delete conn;
        conn = nullptr;
    }
}

void Server::OnConnect(std::function<void(Connection *)> fn) { on_connect_callback_ = std::move(fn); }