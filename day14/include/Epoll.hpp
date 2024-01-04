//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
#include "Macros.hpp"

#include <vector>

#ifdef OS_LINUX
#include <sys/epoll.h>
#endif

class Channel;

class Epoll {
private:
    int epfd_{1};
    struct epoll_event *events_{nullptr};

public:
    Epoll();

    ~Epoll();

    DISALLOW_COPY_AND_MOVE(Epoll);

    void UpdateChannel(Channel *channel);
    void DeleteChannel(Channel* channel);

    std::vector<Channel *> Poll(int timeout = -1);
};