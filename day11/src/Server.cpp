//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Server.hpp"
#include "Socket.hpp"
#include "Acceptor.hpp"
#include "Connection.hpp"
#include <unistd.h>
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

    if (serv_sock->getFd() != -1) {
        Connection *conn = new Connection(loop, serv_sock);
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