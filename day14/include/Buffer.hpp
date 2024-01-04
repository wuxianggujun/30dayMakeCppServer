//
// Created by WuXiangGuJun on 2024/1/3.
//

#pragma once

#include <string>
#include "Macros.hpp"

class Buffer {
private:
    std::string buffer_;

public:
    Buffer() = default;
    ~Buffer() = default;

    DISALLOW_COPY_AND_MOVE(Buffer);

    void Append(const char *_str, int _size);

    ssize_t Size();

    const char *ToStr();

    void Clear();

    void GetLine();
    void SetBuf(const char*);
};


