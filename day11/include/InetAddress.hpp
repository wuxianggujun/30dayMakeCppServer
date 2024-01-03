//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <arpa/inet.h>

class InetAddress {
private:
    struct sockaddr_in addr{};
public:
    InetAddress();

    InetAddress(const char *ip, uint16_t port);

    ~InetAddress();


    void setInetAddr(sockaddr_in _addr);

    sockaddr_in getAddr();
};
