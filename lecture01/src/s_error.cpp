//
// Created by tsuhao on 2021/11/23.
//
#include <iostream>

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    return;
}