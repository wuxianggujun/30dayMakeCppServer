//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "Buffer.hpp"
#include <cstring>
#include <iostream>

Buffer::Buffer() {

}

Buffer::~Buffer() {

}

void Buffer::append(const char *_str, int _size) {
    for (int i = 0; i < _size; ++i) {
        if (_str[i] == '\0') break;
        _buffer.push_back(_str[i]);
    }
}

ssize_t Buffer::size() {
    return _buffer.size();
}

const char *Buffer::c_str() {
    return _buffer.c_str();
}

void Buffer::clear() {
    _buffer.clear();
}

void Buffer::getLine() {
    _buffer.clear();
    std::getline(std::cin, _buffer);
}

void Buffer::setBuf(const char *) {
    _buffer.clear();
    _buffer.append(_buffer);
}