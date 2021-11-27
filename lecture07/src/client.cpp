//
// Created by tsuhao on 2021/11/26.
//

#include <cstdio>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <s_error.h>
#include <unistd.h>

#define BUFFLEN 50

int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen("../../files/recv.txt", "wb");

    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;

    int ret = connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret == -1) {
        error_handling("connet() error");
    }


    char buf[BUFFLEN] = {0};
    int read_cnt = 0;
    //这里注意优先级顺序 read_cnt的赋值要加括号
    while ((read_cnt = read(sock, buf, BUFFLEN)) != 0) {
        if (read_cnt == -1) {
            error_handling("read() error");
            break;
        }
        fwrite((void *) buf, 1, read_cnt, fp);
    }

    while (ret = write(sock, "Bye!", 10) == -1) {}

    fclose(fp);
    close(sock);

    return 0;
}