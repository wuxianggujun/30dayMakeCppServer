//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "EventLoop.hpp"
#include "Epoll.hpp"
#include "Channel.hpp"
#include <vector>

EventLoop::EventLoop() : epoll(nullptr), quit(false) {
    epoll = new Epoll();
}

EventLoop::~EventLoop() {
    delete epoll;
}

void EventLoop::loop() {
    while (!quit) {
        std::vector<Channel *> chs;
        chs = epoll->poll();
        for (auto it = chs.begin(); it != chs.end(); ++it) {
            (*it)->handleEvent();
        }
    }

}

void EventLoop::updateChannel(Channel *channel) {
    epoll->updateChannel(channel);
}
