//
// Created by tsuhao on 2021/12/16.
//

#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void child_proc(int sig) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("Remove proc id:%d \n", pid);
        printf("Child send %d \n", WEXITSTATUS(status));
    }
}

int main(int argc, const char *argv[]) {
    struct sigaction act;
    act.sa_handler = child_proc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();
    if (pid == 0) {
        puts("This is child \n");
        sleep(10);
        return 12;
    } else {
        printf("Child id : %d \n", pid);
        pid = fork();
        if (pid == 0) {
            puts("This is another child");
            sleep(10);
            exit(24);
        }
        printf("Another child id : %d \n", pid);
        for (int i = 0; i < 5; ++i) {
            puts("wait \n");
            sleep(5);
        }
    }

    return 0;
}
