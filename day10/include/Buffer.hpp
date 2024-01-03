//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <string>

class Buffer {
private:
    std::string _buffer;

public:
    Buffer();

    ~Buffer();

    void append(const char *_str, int _size);

    ssize_t size();

    const char *c_str();

    void clear();

    void getLine();
};


