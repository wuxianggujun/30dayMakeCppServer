//
// Created by WuXiangGuJun on 2024/1/3.
//
#pragma once

#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>
#include "Macros.hpp"

class ThreadPool {
private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable condition_Variable_;
    bool stop_{false};

public:
    explicit ThreadPool(unsigned int size = std::thread::hardware_concurrency());

    ~ThreadPool();

    DISALLOW_COPY_AND_MOVE(ThreadPool);

    template<class F, class... Args>
    auto Add(F &&f, Args &&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;
};

template<class F, class... Args>
auto ThreadPool::Add(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);

        if (stop_)
            throw std::runtime_error("add task into stopped ThreadPool");

        tasks_.emplace([task]() { (*task)(); });
    }

    condition_Variable_.notify_one();
    return res;
}