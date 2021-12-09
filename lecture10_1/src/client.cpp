//
// Created by tsuhao on 2021/12/9.
//


#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>

int main(int argc, const char *argv[]) {

    int pid = fork();

    if (pid == 0) {
        sleep(10);
    } else {
        int status;
        while (!waitpid(pid, status, WHOHANG));
        sleep(3);
        puts("sleep 3 sec.");


        if (WIFEXITED(status)) {
            printf("Child send %d \n", WEXITSTATUS(status))
        }

    }

    return 0;
}


