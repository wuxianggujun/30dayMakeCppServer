//
// Created by WuXiangGuJun on 2024/1/3.
//

#include "util.hpp"
#include <cstdio>
#include <cstdlib>

void errif(bool condition, const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}