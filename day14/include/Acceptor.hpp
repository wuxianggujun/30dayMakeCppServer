//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
#include "Macros.hpp"
#include <functional>

class EventLoop;
class Socket;
class Channel;

class Acceptor {
private:
    EventLoop *loop_;
    Socket *socket_;
    Channel *acceptChannel_;
    std::function<void(Socket *)> new_Connection_Callback_;

public:
    explicit Acceptor(EventLoop *_loop);

    ~Acceptor();

    DISALLOW_COPY_AND_MOVE(Acceptor);

    void AcceptConnection();
    void SetNewConnectionCallback(std::function<void(Socket *)> const &callback);
};


