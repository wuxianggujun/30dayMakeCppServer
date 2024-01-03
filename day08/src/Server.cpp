//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Server.hpp"
#include "Socket.hpp"
#include "Acceptor.hpp"
#include "Connection.hpp"
#include <functional>


#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) : loop(_loop), acceptor(nullptr) {
    acceptor = new Acceptor(loop);
    std::function<void(Socket *)> cb = [this](auto &&PH1) { newConnection(std::forward<decltype(PH1)>(PH1)); };
    acceptor->setNewConnectionCallback(cb);
}

Server::~Server() {
    delete acceptor;
}


void Server::newConnection(Socket *serv_sock) {
    Connection *conn = new Connection(loop, serv_sock);
    std::function<void(Socket *)> cb = [this](auto &&PH1) { deleteConnection(std::forward<decltype(PH1)>(PH1)); };
    conn->setDeleteConnectionCallback(cb);
    connections[serv_sock->getFd()] = conn;
}

void Server::deleteConnection(Socket *socket) {
    Connection *conn = connections[socket->getFd()];
    connections.erase(socket->getFd());
    delete conn;
}