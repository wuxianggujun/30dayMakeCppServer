//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <sys/epoll.h>
#include <functional>

class Socket;
class EventLoop;

class Channel {
private:
    EventLoop *loop;
    int fd;
    uint32_t events;
    uint32_t ready;
    bool inEpoll;
    bool useThreadPool;
    std::function<void()> readCallBack;
    std::function<void()> writeCallBack;
public:
    Channel(EventLoop *_loop, int _fd);

    ~Channel();

    void handleEvent();
    void enableRead();

    int getFd();

    uint32_t getEvents();
    uint32_t getReady();

    bool getInEpoll();

    void setInEpoll(bool _in = true);
    void useET();


    void setReady(uint32_t);
    void setReadCallback(std::function<void()>);
    void setUseThreadPool(bool use = true);
};
