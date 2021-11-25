//
// Created by tsuhao on 2021/11/25.
//


#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <s_error.h>
#include <iostream>
#include <unistd.h>

#define BUFFLEN 20

int main(int argc, char *argv[]) {

    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    char msg[BUFFLEN] = "Msg from clnt.";

    struct  sockaddr_in serv_addr, from_addr;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;
    socklen_t addr_len;

    int ret = sendto(sock, msg, BUFFLEN, 0, (sockaddr *)&serv_addr, sizeof(serv_addr));
    if ( ret == -1 ) {
        error_handling("sendto() error");
    }

    addr_len = sizeof(from_addr);
    int strlen = recvfrom(sock, msg, BUFFLEN, 0, (sockaddr *)&from_addr, &addr_len);
    if ( strlen == -1 ) {
        error_handling("recvfrom() error");
    }
    msg[strlen] = 0;
    std::cout <<"Msg from serv: " << msg << std::endl;

    close(sock);

    return 0;
}