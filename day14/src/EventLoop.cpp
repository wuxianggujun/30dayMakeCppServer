//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "EventLoop.hpp"
#include "Epoll.hpp"
#include "Channel.hpp"
#include <vector>

EventLoop::EventLoop() {
    epoll_ = new Epoll();
}

EventLoop::~EventLoop() {
    delete epoll_;
}

void EventLoop::Loop() {
    while (!quit_) {
        std::vector<Channel *> chs;
        chs = epoll_->Poll();
        for (auto &ch:chs){
            ch->HandleEvent();
        }
    }
}

void EventLoop::UpdateChannel(Channel *channel) {
    epoll_->UpdateChannel(channel);
}
