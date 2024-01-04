//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <sys/epoll.h>
#include <vector>

class Channel;

class Epoll {
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();

    ~Epoll();

    void updateChannel(Channel *channel);
    void deleteChannel(Channel*);

    std::vector<Channel *> poll(int timeout = -1);
};