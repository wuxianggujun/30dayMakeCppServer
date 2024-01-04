//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "EventLoop.hpp"
#include "Channel.hpp"
#include "Poller.hpp"
#include <vector>

EventLoop::EventLoop() {
   poller_ = new Poller();
}

EventLoop::~EventLoop() {
    Quit();
    delete poller_;
}

void EventLoop::Loop() {
    while (!quit_) {
        std::vector<Channel *> chs;
        chs = poller_->Poll();
        for (auto &ch:chs){
            ch->HandleEvent();
        }
    }
}

void EventLoop::Quit() {
    quit_ = true;
}

void EventLoop::UpdateChannel(Channel *channel) {
    poller_->UpdateChannel(channel);
}
void EventLoop::DeleteChannel(Channel *channel) {
    poller_->DeleteChannel(channel);
}
