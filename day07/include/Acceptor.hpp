//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <functional>

class EventLoop;

class Socket;

class InetAddress;

class Channel;


class Acceptor {
private:
    EventLoop *loop;
    Socket *socket;
    InetAddress *addr;
    Channel *acceptChannel;

public:
    explicit Acceptor(EventLoop *_loop);

    ~Acceptor();

    void acceptConnection();

    std::function<void(Socket *)> newConnectionCallback;

    void setNewConnectionCallback(std::function<void(Socket *)>);
};


