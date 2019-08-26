//
// Created by Knight on 2019-08-20.
//

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

int test();

int fd = -1;

void signal_handler() {
    printf("signal_handler\n");
}

void *thread_func() {
    printf("%u\n", pthread_self());
    fd = 2;
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork\n");
    } else if (pid == 0) {
        printf("child: %d\n", pid);
        char *args[] = {"cat", NULL};
        execvp("cat", args);
    } else {
        signal(SIGCHLD, signal_handler);
    }

    pthread_exit(NULL);
}

int main() {

//    test();
//    return 0;


    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, NULL);
    printf("fd: %d - thread: %u\n", fd, thread);

    while (1);
    return 0;
    pid_t pid = fork();

    if (pid < 0) {
        err(1, "fork");
    }
    if (pid == 0) {
        printf("child: %d\n", getpid());
        char *args[] = {};
        execvp("ps", args);
    } else {
        printf("parent: pid: %d- child: %d\n", getpid(), pid);
        while (1);
    }

    printf("end\n");
//    FILE *pFile;
//    if ((pFile = popen("adb shell top", "r"))) {
//        int fd = fileno(pFile);
//        struct winsize  ws = {200, 100, 0, 0};
//
////                { 100, 100, 0, 0};
////        ioctl(fd, TIOCSWINSZ, &ws);
//        char buf[512];
//        while (fread(buf, 1, 511, pFile)) {
////            printf("==============\n");
//
//            buf[sizeof(buf) - 1] = '\0';
//            fputs(buf, stdout);
////            printf("==============\n");
//        }
////        printf("==============\n");
////        fputs(buf, stdout);
////        printf("==============\n");
//    }
}

int test() {
    int count = 1;
    int child;

    // child = vfork( );

    printf("Before create son, the father's count is:%d\n", count);

    if ((child = vfork()) < 0) {
        perror("fork error : ");
    } else if (child == 0)     //  fork return 0 in the child process because child can get hid PID by getpid( )
    {
        printf("This is son, his count is: %d (%p). and his pid is: %d\n", ++count, &count, getpid());
//        exit(0);
    } else                    //  the PID of the child process is returned in the parent’s thread of execution
    {

        printf("After son, This is father, his count is: %d (%p), his pid is: %d\n", ++count, &count, getpid());
        sleep(2);
        exit(0);
    }

    return EXIT_SUCCESS;

}

