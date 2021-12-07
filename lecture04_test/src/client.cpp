//
// Created by tsuhao on 2021/11/24.
//



#include <netinet/in.h>
#include <s_error.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>

#define BUFF_LEN 30

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
    char msg[BUFF_LEN] = "Msg from clnt";

    int str_len;

    str_len = read(serv_sock, msg, BUFF_LEN);
    write(serv_sock, msg, str_len);


    close(serv_sock);

    return 0;
}