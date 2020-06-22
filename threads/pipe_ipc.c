//
// Created by Knight on 2020/6/22.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void readAndOut(int i);

int main(void) {

    int fd[2];
    pipe(fd);

    pid_t p = fork();
    int status;
    if (p > 0) {
        close(fd[1]);
        readAndOut(fd[0]);
        do {
            wait(&status);
            printf("wait => %d- %d\n",WEXITSTATUS(status), WIFSIGNALED(status));
        } while (!WEXITSTATUS(status)&& !WIFSIGNALED(status));
    } else if (p == 0) {
        close(fd[0]);
        write(fd[1], "hello world!", 12);
        close(fd[1]);
        sleep(1);
        _exit(5);
    } else {
        perror("fork");
    }
    return 0;
}

void readAndOut(int i) {
    char buf[BUFSIZ];
    int n;
    while ((n = read(i, buf, BUFSIZ))) {
        printf("read %d\n", n);
        write(STDOUT_FILENO, buf, n);
    }
    close(i);
}
