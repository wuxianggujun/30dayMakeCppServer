//
// Created by WuXiangGuJun on 2024/1/4.
//
#include <iostream>
#include <string>

#include "ThreadPool.hpp"

void Print(int a, double b, const char *c, std::string const &d) { std::cout << a << b << c << d << std::endl; }

void Test() { std::cout << "hellp" << std::endl; }

int main(int argc, char const *argv[]) {
    auto *poll = new ThreadPool();
    std::function<void()> func = [] { return Print(1, 3.14, "hello", std::string("world")); };
    poll->Add(func);
    func = Test;
    poll->Add(func);
    delete poll;
    return 0;
}