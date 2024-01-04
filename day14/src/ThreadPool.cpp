//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        workers_.emplace_back([this]() {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex_);
                    condition_Variable_.wait(lock, [this]() { return stop_ || !tasks_.empty(); });
                    if (stop_ && tasks_.empty()) {
                        return;
                    }
                    task = tasks_.front();
                    tasks_.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    condition_Variable_.notify_all();
    for (std::thread &th : workers_) {
        if (th.joinable()) {
            th.join();
        }
    }
}