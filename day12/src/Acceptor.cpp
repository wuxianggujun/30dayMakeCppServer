//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Acceptor.hpp"
#include "Socket.hpp"
#include "Channel.hpp"


Acceptor::Acceptor(EventLoop *_loop) : loop(_loop),socket(nullptr), acceptChannel(nullptr){
    socket = new Socket();
    InetAddress * addr = new InetAddress("127.0.0.1", 1234);
    socket->bind(addr);
    //socket->setnonblocking();
    socket->listen();
    acceptChannel = new Channel(loop, socket->getFd());
    std::function<void()> cb = [this] { acceptConnection(); };
    acceptChannel->setReadCallback(cb);
    acceptChannel->enableRead();
    delete addr;
}

Acceptor::~Acceptor() {
    delete socket;
    delete acceptChannel;
}

void Acceptor::acceptConnection(){
    InetAddress *clnt_addr = new InetAddress();
    Socket *clnt_sock = new Socket(socket->accept(clnt_addr));
    printf("new client fd %d! IP: %s Port: %d\n", clnt_sock->getFd(), inet_ntoa(clnt_addr->getAddr().sin_addr), ntohs(clnt_addr->getAddr().sin_port));
    clnt_sock->setnonblocking();
    newConnectionCallback(clnt_sock);
    delete clnt_addr;
}


void Acceptor::setNewConnectionCallback(std::function<void(Socket *)> _cb) {
    newConnectionCallback = std::move(_cb);
}
