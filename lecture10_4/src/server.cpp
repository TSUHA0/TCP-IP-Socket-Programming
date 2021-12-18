//
// Created by tsuhao on 2021/12/16.
//


#include <sys/wait.h>
#include <cstdio>
#include <netinet/in.h>
#include <cstdlib>
#include <s_error.h>
#include <unistd.h>

void proc_child(int sig) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("Child id: %d \n", pid);
        printf("Child send: %d \n", status);
    }
}

int main(int argc, const char *argv[]) {

    struct sigaction act;
    act.sa_handler = proc_child;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int serv_sock, clnt_sock;
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr, clnt_addr;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_family = AF_INET;

    int ret = bind(serv_sock, (sockaddr *) &serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        error_handling("bind() error");
    }
    ret = listen(serv_sock, 5);
    if (ret < 0) {
        error_handling("listen() error");
    }

    while (1) {
        socklen_t addr_len = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (sockaddr *) &clnt_addr, &addr_len);
        if (ret < 0) {
            error_handling("accept() error");
            break;
        }
        int pid = fork();
        if (pid < 0)
            error_handling("fork() error");
        else if (pid == 0) {
            close(serv_sock);
            char msg[30];
            int len;
            while ((len = read(clnt_sock, msg, sizeof(msg))) > 0) {
                write(clnt_sock, msg, sizeof(msg));
            }
        } else close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}
