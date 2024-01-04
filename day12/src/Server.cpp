//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Server.hpp"
#include "Socket.hpp"
#include "Acceptor.hpp"
#include "Connection.hpp"
#include "ThreadPool.hpp"
#include "EventLoop.hpp"
#include <unistd.h>
#include <functional>


#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) : mainReactor(_loop), acceptor(nullptr) {
    acceptor = new Acceptor(mainReactor);
    std::function<void(Socket *)> cb = [this](auto &&PH1) { newConnection(std::forward<decltype(PH1)>(PH1)); };
    acceptor->setNewConnectionCallback(cb);

    int size = std::thread::hardware_concurrency();

    threadPool = new ThreadPool(size);
    for (int i = 0; i < size; ++i) {
        subReactor.push_back(new EventLoop());
    }

    for (int i = 0; i < size; ++i) {
        std::function<void()> sub_loop = [capture0 = subReactor[i]] { capture0->loop(); };
        threadPool->add(sub_loop);;
    }
}

Server::~Server() {
    delete acceptor;
    delete threadPool;
}


void Server::newConnection(Socket *serv_sock) {

    if (serv_sock->getFd() != -1) {
        int random = serv_sock->getFd() % subReactor.size();
        Connection *conn = new Connection(subReactor[random], serv_sock);
        std::function<void(int)> cb = [this](auto &&PH1) { deleteConnection(std::forward<decltype(PH1)>(PH1)); };
        conn->setDeleteConnectionCallback(cb);// 绑定删除连接的回调函数
        connections[serv_sock->getFd()] = conn;
    }

}

void Server::deleteConnection(int sockfd) {
    if (sockfd != -1) {
        auto it = connections.find(sockfd);
        if (it != connections.end()) {
            Connection *conn = connections[sockfd];
            connections.erase(sockfd);
            delete conn;
        }
    }
}