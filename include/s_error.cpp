//
// Created by tsuhao on 2021/11/23.
//
#include <iostream>

void error_handling(const char *msg){
    fputc(msg, stderr);
    fputc("\n", stderr);
    return;
}