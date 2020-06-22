//
// Created by Knight on 2020/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int god = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void mutex_clean(void *pVoid) {
    pthread_mutex_unlock(&mutex);
}

void producer(int *t) {

    while (1) {
        pthread_mutex_lock(&mutex);
        pthread_cleanup_push(mutex_clean, &mutex);
            printf("----- producer-start-%ld-----\n", pthread_self());
            printf("producer-%ld lock god: %d\n", pthread_self(), god);
            sleep(*t);
            while (god == 5) {
                printf("producer-%ld while pthread_cond_wait god:%d\n", pthread_self(), god);
                pthread_cond_wait(&cond, &mutex);
            }
//        printf("producer-%ld unlock god: %d\n", pthread_self(), god);
//        pthread_mutex_unlock(&mutex);
//        pthread_mutex_lock(&mutex);
//        printf("producer-%ld lock god: %d\n", pthread_self(), god);
            if (god == 5) {
                printf("producer-%ld if pthread_cond_wait god:%d\n", pthread_self(), god);
                pthread_cond_wait(&cond, &mutex);
            } else {
                printf("producer-%ld pthread_cond_broadcast god: %d\n", pthread_self(), god);
                god++;
                pthread_cond_broadcast(&cond);
            }
            printf("producer-%ld unlock god: %d\n", pthread_self(), god);
            printf("----- producer-end-%ld-----\n", pthread_self());
        pthread_cleanup_pop(mutex_clean);
        pthread_mutex_unlock(&mutex);
    }

}

void consumer(int *t) {
    while (true) {
        pthread_mutex_lock(&mutex);
        pthread_cleanup_push(mutex_clean, &mutex);
            printf("----- consumer-start-%ld-----\n", pthread_self());
            printf("consumer-%ld lock god: %d\n", pthread_self(), god);
            sleep(*t);
            while (god == 0) {
                printf("consumer-%ld while pthread_cond_wait god:%d\n", pthread_self(), god);
                pthread_cond_wait(&cond, &mutex);
            }
//        printf("consumer-%ld unlock god: %d\n", pthread_self(), god);
//        pthread_mutex_unlock(&mutex);
//        pthread_mutex_lock(&mutex);
//        printf("consumer-%ld lock god: %d\n", pthread_self(), god);
            if (god == 0) {
                printf("consumer-%ld if pthread_cond_wait god:%d\n", pthread_self(), god);
                pthread_cond_wait(&cond, &mutex);
            } else {
                printf("consumer-%ld pthread_cond_broadcast god: %d\n", pthread_self(), god);
                god--;
                pthread_cond_broadcast(&cond);
            }
            printf("consumer-%ld unlock god: %d\n", pthread_self(), god);
            printf("----- consumer-end-%ld-----\n", pthread_self());
        pthread_cleanup_pop(mutex_clean);
        pthread_mutex_unlock(&mutex);
    }
}

int main(void) {
    printf("----- -----\n");
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;
    pthread_t t5;

    int p1 = 1;
    int p2 = 2;
    int c3 = 3;
    int p4 = 4;
    int c5 = 5;

    int np1 = pthread_create(&t1, NULL, reinterpret_cast<void *(*)(void *)>(&producer), &p1);
    int np2 = pthread_create(&t1, NULL, reinterpret_cast<void *(*)(void *)>(&producer), &p1);
    int nc3 = pthread_create(&t1, NULL, reinterpret_cast<void *(*)(void *)>(&consumer), &p1);
    int np4 = pthread_create(&t1, NULL, reinterpret_cast<void *(*)(void *)>(&producer), &p1);
    int nc5 = pthread_create(&t1, NULL, reinterpret_cast<void *(*)(void *)>(&consumer), &p1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    printf("----- -----\n");
    return 0;
}
