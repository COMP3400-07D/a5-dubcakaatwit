#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s prog1 prog2\n", argv[0]);
        return 1;
    }

    int fds[2];
    if (pipe(fds) < 0) {
        perror("pipe");
        return 1;
    }

    pid_t p1 = fork();
    if (p1 < 0) {
        perror("fork");
        return 1;
    }

    if (p1 == 0) {
        dup2(fds[1], STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);
        execlp(argv[1], argv[1], NULL);
        perror("exec");
        _exit(127);
    }

    pid_t p2 = fork();
    if (p2 < 0) {
        perror("fork");
        return 1;
    }

    if (p2 == 0) {
        // Child 2 — reads from pipe
        dup2(fds[0], STDIN_FILENO);
        close(fds[1]);
        close(fds[0]);
        execlp(argv[2], argv[2], NULL);
        perror("exec");
        _exit(127);
    }

    close(fds[0]);
    close(fds[1]);

    int st1, st2;
    waitpid(p1, &st1, 0);
    waitpid(p2, &st2, 0);

    return 0;
}