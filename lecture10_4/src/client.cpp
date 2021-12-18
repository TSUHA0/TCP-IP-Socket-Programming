//
// Created by tsuhao on 2021/12/16.
//
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_LEN 50

void write_routine(int sock, char *buf) {
    while (1) {
        fgets(buf, BUFF_LEN, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf));
    }
}

void read_routine(int sock, char *buf) {
    int str_len;
    while ((str_len = read(sock, buf, BUFF_LEN)) > 0) {
        fputs(buf, stdout);
    }
}

int main(int argc, const char *argv[]) {
    char buf[BUFF_LEN];


    return 0;
}