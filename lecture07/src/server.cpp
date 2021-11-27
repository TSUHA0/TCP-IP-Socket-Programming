//
// Created by tsuhao on 2021/11/26.
//

#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <s_error.h>
#include <unistd.h>
#include <iostream>

#define BUFFLEN 50

int main(int argc, char *argv[]) {

    FILE *fp;
    fp = fopen("../../files/send.txt", "rb");

    int serv_sock, clnt_sock;
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;

    int ret = bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        error_handling("bind() error");
    }

    ret = listen(serv_sock, 1);
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
        int read_cnt = fread((void *) buf, 1, BUFFLEN, fp);
        if (read_cnt < BUFFLEN) {
            int ret = write(clnt_sock, buf, read_cnt);
            if (ret == -1) {
                error_handling("write() error");
            }
            break;
        }
        write(clnt_sock, buf, BUFFLEN);
    }

    shutdown(clnt_sock, SHUT_WR);
    read(clnt_sock, buf, BUFFLEN);
    std::cout << "Msg from client: " << buf << std::endl;

    fclose(fp);
    close(serv_sock);
    close(clnt_sock);

    return 0;
}