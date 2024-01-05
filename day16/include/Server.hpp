//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
#include "Macros.hpp"

#include <map>
#include <vector>
#include <functional>

class EventLoop;

class Socket;

class Acceptor;

class Connection;

class ThreadPool;

class Server {
private:
    EventLoop *main_Reactor_; // 时间循环
    Acceptor *acceptor_; // 用于接受TCP连接
    std::map<int, Connection *> connections_; // 所有TCP连接
    std::vector<EventLoop *> sub_Reactor_;
    ThreadPool *thread_Pool_;
    std::function<void(Connection *)> on_connect_callback_; // 处理客户端请求
    std::function<void(Connection *)> on_message_callback_; // 处理客户端请求
    std::function<void(Connection *)> new_connect_callback_; // 处理客户端请求
public:
    explicit Server(EventLoop * loop);

    ~Server();

    DISALLOW_COPY_AND_MOVE(Server);

    void NewConnection(Socket* sock);
    void DeleteConnection(Socket *sock); // 断开TCP连接
    void OnConnect(std::function<void(Connection *)> fn);
    void OnMessage(std::function<void(Connection *)> fn);
    void NewConnect(std::function<void(Connection *)> fn);
};


