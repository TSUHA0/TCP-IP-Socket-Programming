//
// Created by tsuhao on 2021/11/23.
//

#include <arpa/inet.h>
// #include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <s_error.h>
#include <unistd.h>
#include <cstdio>


int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char msg[30];
    int str_len;
    int ret;

    if (argc != 3) {
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_family = AF_INET;

    ret = connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr));
    if ( ret != 0 ) {
        error_handling("connect() error");
    }

    str_len = read(sock, msg, sizeof(msg)-1);

    printf("Msg from server %s", msg);
    close(sock);

    return 0;
}
