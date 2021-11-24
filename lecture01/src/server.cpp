//
// Created by tsuhao on 2021/11/23.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <s_error.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int serv_sock;
    int clnt_sock;
    int ret;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char msg[] = "Hello from server.";

    if (argc != 2) {
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( serv_sock == -1 ) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;

    ret = bind(serv_sock, (sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret != 0) {
        error_handling("bind() error");
    }

    ret = listen(serv_sock, 5);
    if (ret != 0) {
        error_handling("listen() error");
    }
    clnt_addr_size = sizeof(clnt_addr_size);
    clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }

    write(clnt_sock, msg, sizeof(msg));
    close(serv_sock);
    close(clnt_sock);
    return 0;
}