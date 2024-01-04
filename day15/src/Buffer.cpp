//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Buffer.hpp"
#include <cstring>
#include <iostream>

void Buffer::Append(const char *str, int size) {
    for (int i = 0; i < size; ++i) {
        if (str[i] == '\0') break;
        buffer_.push_back(str[i]);
    }
}

ssize_t Buffer::Size() {
    return buffer_.size();
}

const char *Buffer::ToStr() {
    return buffer_.c_str();
}

void Buffer::Clear() {
    buffer_.clear();
}

void Buffer::GetLine() {
    buffer_.clear();
    std::getline(std::cin, buffer_);
}

void Buffer::SetBuf(const char * buf) {
    buffer_.clear();
    buffer_.append(buf);
}