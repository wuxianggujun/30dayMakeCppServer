//
// Created by WuXiangGuJun on 2024/1/3.
//
#include "Channel.hpp"
#include <unistd.h>
#include "Socket.hpp"
#include "EventLoop.hpp"
#include <sys/epoll.h>

Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), events(0), ready(0), inEpoll(false) {

}

Channel::~Channel() {
    if (fd != -1) {
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent() {
    if (ready & (EPOLLIN | EPOLLPRI)) {
        readCallBack();
    }
    if (ready & (EPOLLOUT)) {
        writeCallBack();
    }
}

void Channel::enableRead() {
    events = EPOLLIN | EPOLLET;
    loop->updateChannel(this);
}

void Channel::useET() {
    events != EPOLLET;
    loop->updateChannel(this);
}

int Channel::getFd() {
    return fd;
}

uint32_t Channel::getEvents() {
    return events;
}

uint32_t Channel::getReady() {
    return ready;
}

bool Channel::getInEpoll() {
    return inEpoll;
}

void Channel::setInEpoll(bool _in) {
    inEpoll = _in;
}

void Channel::setReady(uint32_t _ev) {
    ready = _ev;
}

void Channel::setReadCallback(std::function<void()> _cb) {
    readCallBack = std::move(_cb);
}
