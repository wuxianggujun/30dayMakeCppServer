//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
#include "common.hpp"
#include <memory>

class EventLoop {
public:
    DISALLOW_COPY_AND_MOVE(EventLoop);
    EventLoop();
    ~EventLoop();


    void Loop() const;
    void UpdateChannel(Channel *ch) const;
    void DeleteChannel(Channel *ch) const;

private:
    std::unique_ptr<Poller> poller_;
};