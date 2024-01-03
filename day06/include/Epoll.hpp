//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <sys/epoll.h>
#include <vector>
#include "Channel.hpp"

class Channel;

class Epoll {
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();

    ~Epoll();

    void addFd(int fd, uint32_t op);

    void updateChannel(Channel *channel);

//    std::vector<epoll_event> poll(int timeout = -1);
    std::vector<Channel *> poll(int timeout = -1);
};