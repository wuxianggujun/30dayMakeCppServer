//
// Created by WuXiangGuJun on 2024/1/5.
//
#pragma once
#include "common.hpp"
#include <vector>

#ifdef OS_LINUX
#include <sys/epoll.h>
#endif

#ifdef OS_MACOS
#include <sys/event.h>
#endif

class Poller {
public:
    DISALLOW_COPY_AND_MOVE(Poller);
    Poller();
    ~Poller();

    RC UpdateChannel(Channel *ch) const;
    RC DeleteChannel(Channel *ch) const;

    std::vector<Channel *> Poll(long timeout = -1) const;

private:
    int fd_;

#ifdef OS_LINUX
    struct epoll_event *events_{nullptr};
#endif

#ifdef OS_MACOS
    struct kevent *events_;
#endif
};
