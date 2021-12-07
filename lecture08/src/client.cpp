//
// Created by tsuhao on 2021/12/7.
//

#include <netdb.h>
#include <s_error.h>
#include <iostream>
#include <arpa/inet.h>

int main(int argc, const char *argv[]) {
    hostent *host;
    host = gethostbyname(argv[1]);
    if (!host) {
        error_handling("gethost error");
    }

    printf("Official name: %s \n", host->h_name);
    for (int i = 0; host->h_aliases[i]; ++i) {
        printf("aliases %d:%s \n", i + 1, host->h_aliases[i]);
    }
    printf("Addr type: %s \n", host->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");

    for (int i = 0; host->h_addr_list[i]; ++i) {
        printf("addr %d:%s \n", i + 1, inet_ntoa(*(struct in_addr *) host->h_addr_list[i]));
    }

    return 0;
}