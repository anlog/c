
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void do_threads();

int start = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {

    printf("hello world!\n");

    printf("pid: %d - %d \n", getpid(), getppid());

    do_threads();
    return 0;
}

void *loop_thread(int *k) {
    pthread_mutex_lock(&mutex);
    printf("%d\n", k ? *k : 0);
//    while (1) {
    printf("will sleep %d - %d : %d - %d - %d\n", k ? *k : 0, start, getpid(), getppid(), pthread_self());
    while (start) {
        if (k) {
            printf("A-%d-%d\n", *k, start);
        } else {
            printf("B-%d-%d\n", k, start);
        }
    }
    pthread_mutex_unlock(&mutex);
//        sleep(1);
//    }
}

void do_threads() {
    printf("== %d - %d - %d\n", getpid(), getppid(), pthread_self());
    pthread_t t, t2;
    pthread_mutex_lock(&mutex);
    printf("lock\n");
    int tid = pthread_create(&t, NULL, loop_thread, NULL);
    int a = 1;
    int tid2 = pthread_create(&t2, NULL, loop_thread, &a);

    start = 0;
    printf("unlock\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);

    pthread_join(t, NULL);
    pthread_join(t2, NULL);
}