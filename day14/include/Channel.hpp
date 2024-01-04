//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include "Macros.hpp"
#include <functional>

class Socket;
class EventLoop;

class Channel {
private:
    EventLoop *loop_;
    int fd_;
    uint32_t listen_events_;
    uint32_t ready_events_;
    bool in_epoll_;
    std::function<void()> read_CallBack_;
    std::function<void()> write_CallBack_;

public:
    Channel(EventLoop *_loop, int _fd);
    ~Channel();

    DISALLOW_COPY_AND_MOVE(Channel);

    void HandleEvent();
    void EnableRead();

    int GetFd();

    uint32_t GetListenEvents();
    uint32_t GetReadyEvents();

    bool GetInEpoll();

    void SetInEpoll(bool _in = true);
    void UseET();


    void SetReadyEvents(uint32_t ev);
    void SetReadCallback(std::function<void()> const &callback);
};
