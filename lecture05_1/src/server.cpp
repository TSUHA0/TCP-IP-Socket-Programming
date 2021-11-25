//
// Created by tsuhao on 2021/11/25.
//

#include <netinet/in.h>
#include <iostream>
#include <s_error.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>


#define BUFFLEN 20

int main(int argc, char *argv[]) {

    struct sockaddr_in clnt_addr, serv_addr;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    char msg[BUFFLEN];
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;
    int ret = bind(sock, (sockaddr *)&serv_addr, sizeof(serv_addr));
    if ( ret == -1 ) {
        error_handling("bind() error");
    }

    socklen_t addr_len = sizeof(sockaddr_in);
    int str_len = recvfrom(sock, msg, BUFFLEN, 0, (sockaddr *)&clnt_addr, &addr_len);
    if ( str_len == -1 ) {
        error_handling("recvfrom() error");
    }
    msg[BUFFLEN] = 20;

    std::cout << "Msg from client: " << msg << std::endl;

    char serv_msg[BUFFLEN] = "Msg from serv.";
    ret = sendto(sock, serv_msg, BUFFLEN, 0, (sockaddr *)&clnt_addr, addr_len);;
    if ( ret == -1 ) {
        error_handling("sendto() error");
    }

    close(sock);

    return 0;
}