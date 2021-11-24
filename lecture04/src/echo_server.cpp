//
// Created by tsuhao on 2021/11/24.
//

#include <netinet/in.h>
#include <cstdlib>
#include <s_error.h>
#include <cstdio>
#include <unistd.h>

#define BUFF_LEN 30

int main(int argc, char *argv[]) {
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_len;
    int serv_sock, clnt_sock;
    char msg[BUFF_LEN];

    if (argc != 2) {
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = AF_INET;

    int ret = bind(serv_sock, (sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        error_handling("bind() error");
    }

    ret = listen(serv_sock, 5);
    if (ret == -1) {
        error_handling("listen() error");
    }

    for (int i = 0; i < 5; ++i) {
        clnt_len = sizeof(sockaddr_in);
        clnt_sock = accept(serv_sock, (sockaddr *) &clnt_addr, &clnt_len);
        //sprintf(msg, "You are No.%d client.", i);
        if (clnt_sock == -1) {
            error_handling("accept() error");
            continue;
        }
        printf("No.%d client connect. \n", i+1);
        int str_len;
        while(str_len = read(clnt_sock, msg, BUFF_LEN) != 0){
            write(clnt_sock, msg, str_len);
        }
        close(clnt_sock);
    }
    printf("bye! \n");
    close(serv_sock);
    return 0;
}