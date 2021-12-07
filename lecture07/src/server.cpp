//
// Created by tsuhao on 2021/11/26.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <s_error.h>


#define BUFFLEN 30

int main(int argc, char *argv[]) {

    int ret;
    FILE *fp;
    fp = fopen("../files/send.txt", "rb");
    if (fp == nullptr) {
        error_handling("fopen() error");
    }

    int serv_sock, clnt_sock;
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;

//    int optval = 1;
//    ret = setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
//    if (ret == -1) {
//        error_handling("setsockopt() error");
//    }

    ret = bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        error_handling("bind() error");
    }

    ret = listen(serv_sock, 5);
    if (ret == -1) {
        error_handling("listen() error");
    }

    struct sockaddr_in clnt_addr;
    socklen_t clnt_len = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (sockaddr *) &clnt_addr, &clnt_len);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }

    char buf[BUFFLEN];
    while (1) {
        int read_cnt = fread((void *) buf, BUFFLEN, BUFFLEN, fp);
        if (read_cnt < BUFFLEN) {
            write(clnt_sock, buf, read_cnt);
            printf("last clnt_sock: %s\n", buf);
            break;
        }
        write(clnt_sock, buf, BUFFLEN);
        printf("file clnt_sock: %s\n", buf);
    }

    shutdown(clnt_sock, SHUT_WR);

    while (read(clnt_sock, buf, BUFFLEN) != 0) {
        printf("clnt_sock: %s\n", buf);
    }

    fclose(fp);
    close(clnt_sock);
    int i = 0;
    while (read(serv_sock, buf, BUFFLEN) != 0 && i++ < 7) {
        printf("serv_sock: %s\n", buf);
    }
    close(serv_sock);

    return 0;
}