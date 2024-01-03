//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once
class InetAddress;

class Socket{
private:
    int fd;

public:
    Socket();
    explicit Socket(int _fd);
    ~Socket();

    void bind(InetAddress*);
    void listen();
    void setnonblocking();

    int accept(InetAddress*);
    void connect(InetAddress*);
    int getFd();
};
