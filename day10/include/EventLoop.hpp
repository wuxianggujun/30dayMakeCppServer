//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
#include <functional>

class Epoll;
class Channel;
class ThreadPool;

class EventLoop {

private:
    Epoll *epoll;
    ThreadPool *threadPool;
    bool quit;

public:
    EventLoop();

    ~EventLoop();

    void loop();

    void updateChannel(Channel *channel);
    void addThread(const std::function<void()>&);
};
