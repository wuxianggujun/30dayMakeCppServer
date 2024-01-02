//
// Created by WuXiangGuJun on 2024/1/2.
//
#include "util.hpp"
#include <cstdio>
#include <cstdlib>

void errif(bool condition, const char *errorMessage){
    if(condition){
        perror(errorMessage);
        exit(EXIT_FAILURE);
    }
}