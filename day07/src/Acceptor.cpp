//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Acceptor.hpp"

#include <utility>
#include "Socket.hpp"
#include "InetAddress.hpp"
#include "Channel.hpp"
#include "Server.hpp"


Acceptor::Acceptor(EventLoop *_loop) : loop(_loop) {
    socket = new Socket();
    addr = new InetAddress("127.0.0.1", 8888);
    socket->bind(addr);
    socket->listen();
    socket->setnonblocking();
    acceptChannel = new Channel(loop, socket->getFd());
    std::function<void()> cb = [this] { acceptConnection(); };
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor() {
    delete socket;
    delete addr;
    delete acceptChannel;
}

void Acceptor::acceptConnection() {
    newConnectionCallback(socket);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket *)> _cb) {
    newConnectionCallback = std::move(_cb);
}
