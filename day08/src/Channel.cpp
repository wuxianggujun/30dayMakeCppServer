//
// Created by WuXiangGuJun on 2024/1/3.
//
#include "Channel.hpp"
#include <unistd.h>
#include "EventLoop.hpp"

Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), events(0), revents(0), inEpoll(false) {

}

Channel::~Channel() {
    if (fd != -1){
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent() {
    callBack();
}

void Channel::enableReading() {
    events = EPOLLIN | EPOLLET;
    loop->updateChannel(this);
}

int Channel::getFd() {
    return fd;
}

uint32_t Channel::getEvents() {
    return events;
}

uint32_t Channel::getRevents() {
    return revents;
}

bool Channel::getInEpoll() {
    return inEpoll;
}

void Channel::setInEpoll() {
    inEpoll = true;
}

void Channel::setRevents(uint32_t ev) {
    this->revents = ev;
}

void Channel::setCallback(std::function<void()> _cb) {
    callBack = std::move(_cb);
}

