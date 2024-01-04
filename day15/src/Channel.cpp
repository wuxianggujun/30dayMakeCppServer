//
// Created by WuXiangGuJun on 2024/1/3.
//
#include "Channel.hpp"
#include <unistd.h>
#include <utility>
#include "Socket.hpp"
#include "EventLoop.hpp"

const int Channel::READ_EVENT = 1;
const int Channel::WRITE_EVENT = 2;
const int Channel::ET = 4;

Channel::Channel(EventLoop *loop, Socket *socket) : loop_(loop), socket_(socket) {}

Channel::~Channel() {
    loop_->DeleteChannel(this);
}

void Channel::HandleEvent() {
    if (ready_events_ & READ_EVENT) {
        read_CallBack_();
    }
    if (ready_events_ & WRITE_EVENT) {
        write_CallBack_();
    }
}

// 位操作的写法允许开发者通过按位设置来添加或修改监听事件。
// 在这个例子中，| 操作符将 listen_events_ 中的位与 EPOLLIN 和 EPOLLPRI 中的位进行逻辑或操作，
// 从而在 listen_events_ 中设置相应的位。
void Channel::EnableRead() {
    listen_events_ |= READ_EVENT;
    loop_->UpdateChannel(this);
}

void Channel::EnableWrite() {
    listen_events_ |= WRITE_EVENT;
    loop_->UpdateChannel(this);
}

void Channel::UseET() {
    listen_events_ |= ET;
    loop_->UpdateChannel(this);
}

Socket *Channel::GetSocket() {
    return socket_;
}

int Channel::GetListenEvents() {
    return listen_events_;
}

int Channel::GetReadyEvents() {
    return ready_events_;
}

bool Channel::GetExist() {
    return exist_;
}


void Channel::SetExist(bool in) {
    exist_ = in;
}

void Channel::SetReadyEvents(int ev) {
    if (ev & READ_EVENT) {
        ready_events_ |= READ_EVENT;
    }
    if (ev & WRITE_EVENT) {
        ready_events_ |= WRITE_EVENT;
    }
    if (ev & ET) {
        ready_events_ |= ET;
    }
}

void Channel::SetReadCallback(std::function<void()> const &callback) {
    read_CallBack_ = callback;
}

void Channel::SetWriteCallback(std::function<void()> const &callback) {
    write_CallBack_ = callback;
}
