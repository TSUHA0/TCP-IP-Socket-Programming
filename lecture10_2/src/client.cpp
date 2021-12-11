//
// Created by tsuhao on 2021/12/9.
//


#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>

void timeout(int sig) {
    if (sig == SIGALRM) {
        puts("Time out");
    }
    alarm(2);
}

void keycontrol(int sig) {
    if (sig == SIGINT)
        puts("CTRL+C pressed");
}

int main(int argc, const char *argv[]) {

    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for (int i = 0; i < 3; ++i) {
        puts("wait");
        sleep(100);
    }

    return 0;
}


