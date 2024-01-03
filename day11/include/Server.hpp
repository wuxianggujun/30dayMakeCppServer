//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <map>
class EventLoop;
class Socket;
class Acceptor;
class Connection;

class Server {
private:
    EventLoop *loop; // 时间循环
    Acceptor *acceptor; // 用于接受TCP连接
    std::map<int,Connection*> connections; // 所有TCP连接
public:
    Server(EventLoop*);
    ~Server();

    void handleReadEvent(int); // 处理客户端请求
    void newConnection(Socket *serv_sock); // 新建TCP连接
    void deleteConnection(int socket); // 断开TCP连接
};


