//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <sys/epoll.h>
#include <functional>

class EventLoop;

class Channel {
private:
    EventLoop *loop;
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;
    std::function<void()> callBack;
public:
    Channel(EventLoop *_loop, int _fd);

    ~Channel();

    void handleEvent();
    void enableReading();

    int getFd();

    uint32_t getEvents();
    uint32_t getRevents();

    bool getInEpoll();

    void setInEpoll();

    void setRevents(uint32_t revents);
    void setCallback(std::function<void()>);
};
