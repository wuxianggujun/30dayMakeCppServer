//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
#include "Macros.hpp"
#include <functional>

class Epoll;
class Channel;

class EventLoop {

private:
    Epoll *epoll_{nullptr};
    bool quit_{false};

public:
    EventLoop();

    ~EventLoop();

    DISALLOW_COPY_AND_MOVE(EventLoop);

    void Loop();
    void UpdateChannel(Channel *channel);
};
