//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <functional>
#include <cstdio>

class EventLoop;
class Socket;
class Channel;

class Acceptor {
private:
    EventLoop *loop;
    Socket *socket;
    Channel *acceptChannel;
    std::function<void(Socket *)> newConnectionCallback;

public:
    explicit Acceptor(EventLoop *_loop);

    ~Acceptor();

    void acceptConnection();
    void setNewConnectionCallback(std::function<void(Socket *)>);
};


