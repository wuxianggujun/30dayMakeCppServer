//
// Created by WuXiangGuJun on 2024/1/3.
//
#include "Channel.hpp"
#include <unistd.h>
#include <utility>
#include "Socket.hpp"
#include "EventLoop.hpp"
#include <sys/epoll.h>

Channel::Channel(EventLoop *loop, int fd) : loop_(loop), fd_(fd), listen_events_(0), ready_events_(0),
                                            in_epoll_(false) {}

Channel::~Channel() {
    if (fd_ != -1) {
        close(fd_);
        fd_ = -1;
    }
}

void Channel::HandleEvent() {
    if (ready_events_ & (EPOLLIN | EPOLLPRI)) {
        read_CallBack_();
    }
    if (ready_events_ & (EPOLLOUT)) {
        write_CallBack_();
    }
}

// 位操作的写法允许开发者通过按位设置来添加或修改监听事件。
// 在这个例子中，| 操作符将 listen_events_ 中的位与 EPOLLIN 和 EPOLLPRI 中的位进行逻辑或操作，
// 从而在 listen_events_ 中设置相应的位。
void Channel::EnableRead() {
    listen_events_ |= EPOLLIN | EPOLLPRI;
    loop_->UpdateChannel(this);
}

void Channel::UseET() {
    listen_events_ |= EPOLLET;
    loop_->UpdateChannel(this);
}

int Channel::GetFd() {
    return fd_;
}

uint32_t Channel::GetListenEvents() {
    return listen_events_;
}

uint32_t Channel::GetReadyEvents() {
    return ready_events_;
}

bool Channel::GetInEpoll() {
    return in_epoll_;
}


void Channel::SetInEpoll(bool in) {
    in_epoll_ = in;
}

void Channel::SetReadyEvents(uint32_t ev) {
    ready_events_ = ev;
}

void Channel::SetReadCallback(std::function<void()> const &callback) {
    read_CallBack_ = callback;
}
