//
// Created by WuXiangGuJun on 2024/1/5.
//
#pragma once
#include "common.hpp"
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

class TcpServer {
public:
    DISALLOW_COPY_AND_MOVE(TcpServer);
    TcpServer();
    ~TcpServer();
    void Start();

    RC NewConnection(int fd);
    RC DeleteConnection(int fd);

    void onConnect(std::function<void(Connection *)> fn);
    void onRecv(std::function<void(Connection *)> fn);

private:
    std::unique_ptr<EventLoop> main_reactor_;
    std::unique_ptr<Acceptor> acceptor_;

    std::unordered_map<int, std::unique_ptr<Connection>> connections_;
    std::vector<std::unique_ptr<EventLoop>> sub_reactors_;

    std::unique_ptr<ThreadPool> thread_pool_;

    std::function<void(Connection *)> on_connect_;
    std::function<void(Connection *)> on_recv_;
};
