//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Acceptor.hpp"
#include "Socket.hpp"
#include "Channel.hpp"
#include <utility>


Acceptor::Acceptor(EventLoop * loop) : loop_(loop),socket_(nullptr), acceptChannel_(nullptr){
    socket_ = new Socket();
    auto * addr = new InetAddress("127.0.0.1", 1234);
    socket_->Bind(addr);
    //socket->setnonblocking();
    socket_->Listen();
    acceptChannel_ = new Channel(loop, socket_->GetFd());
    std::function<void()> cb = [this] { AcceptConnection(); };
    acceptChannel_->SetReadCallback(cb);
    acceptChannel_->EnableRead();
    delete addr;
}

Acceptor::~Acceptor() {
    delete acceptChannel_;
    delete socket_;
}

void Acceptor::AcceptConnection() {
    auto *clnt_addr = new InetAddress();
    auto *clnt_sock = new Socket(socket_->Accept(clnt_addr));
    printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->GetFd(), clnt_addr->GetIp(), clnt_addr->GetPort());
    clnt_sock->SetNonBlocking();
    new_Connection_Callback_(clnt_sock);
    delete clnt_addr;
}


void Acceptor::SetNewConnectionCallback(std::function<void(Socket *)> const &callback) {
    new_Connection_Callback_ = callback;
}
