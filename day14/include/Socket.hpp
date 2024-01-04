//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <arpa/inet.h>
#include "Macros.hpp"

class InetAddress {
private:
    struct sockaddr_in addr_{};
public:
    InetAddress();

    InetAddress(const char *ip, uint16_t port);

    ~InetAddress() = default;

    DISALLOW_COPY_AND_MOVE(InetAddress);

    void SetAddr(sockaddr_in addr);

    sockaddr_in GetAddr();

    const char *GetIp();

    uint16_t GetPort();
};

class Socket {
private:
    int fd_{-1};

public:
    Socket();

    explicit Socket(int _fd);

    ~Socket();

    DISALLOW_COPY_AND_MOVE(Socket);

    void Bind(InetAddress * addr);

    void Listen();

    int Accept(InetAddress * addr);

    void Connect(InetAddress * addr);
    void Connect(const char*ip,uint16_t port);

    void SetNonBlocking();
    bool IsNonBlocking();
    int GetFd();
};
