//
// Created by tsuhao on 2021/11/24.
//
#include <netinet/in.h>
#include <s_error.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <cstring>

#define BUF_SIZE 30

int main(int argc, char *argv[]) {
    struct sockaddr_in serv_addr;
    int serv_sock;
    int ret;

    if (argc != 3) {
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        error_handling("socket() error");
    }

    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_family = AF_INET;

    ret = connect(serv_sock, (sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        error_handling("connect() error");
    }
    char message[BUF_SIZE];

    while (1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") | !strcmp(message, "Q\n")) {
            break;
        }

        write(serv_sock, message, strlen(message));
        int str_len = read(serv_sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message from server: %s \n", message);
    }

    close(serv_sock);
    return 0;
}