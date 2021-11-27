//
// Created by tsuhao on 2021/11/26.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>
#include <s_error.h>
#include <iostream>

#define BUFFLEN 20

int main(int argc, char *argv[]) {

    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv_addr;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family =AF_INET;

    int ret = connect(sock,(sockaddr *)&serv_addr, sizeof(serv_addr));
    if ( ret == -1 ) {
        error_handling("connect() error");
    }
    char msg[] = "Msg from bind sock udp";
    ret = write(sock,msg, sizeof(msg));
    if ( ret == -1 ) {
        error_handling("write() error");
    }

    char recv_msg[BUFFLEN];
    int strlen = read(sock,recv_msg,BUFFLEN);
    if ( strlen == -1 ) {
        error_handling("read() error");
    }

    std::cout << recv_msg <<std::endl;

    return 0;
}