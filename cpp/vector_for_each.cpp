#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <unistd.h>

#define XXX "hello"

void test();

//
// Created by Knight on 2019/8/27.
//

char **testXX(int size);

char **hello;

int main() {

    char **p = testXX(4);

    char **pp = p;
    for (int j = 0; j < 4; ++j) {
        printf("==testXX=%s=%p=\n", *pp, *pp);
//        free(*pp);
    }
    free(p);
    return 0;
    std::vector<char *> vector_t;
    vector_t.emplace_back(strdup("hello"));
    vector_t.emplace_back(strdup("world!!"));

    for (auto const &i: vector_t) {
        printf("====%s=%p=\n", i, i);
    }
    return 0;

    char *a;
    int bb;
    test();

    printf("=hello=====%s====%p--%p\n", hello[0], hello[0], hello);
    printf("======%s====%p\n", a, a);
    printf("======%d====%p\n", bb, bb);

    if (fork() == 0) {
        printf("=hello=====%s====%p--%p\n", hello[0], hello[0], hello);
    }
    return 1;

    std::vector<char *> tmp;
//    char *a = strdup("ls");
    char *b = strdup("-al");
    tmp.push_back(a);
    tmp.push_back(b);

    std::for_each(tmp.cbegin(), tmp.cend(), [](char *xx) { printf("=%s=\n", xx); });

    unsigned long size = tmp.size();
    char *args[size];
    char **args_p = args;

    for (auto const &argc: tmp) {
        *args_p++ = argc;
//        printf("=%s=\n", item);
    }

    for (unsigned long i = 0; i < sizeof(args) / sizeof(*args); i++) {
        printf("======args==%s==\n", args[i]);
    }
    printf(": %d\n", size);

    printf("===================fork============\n");

    pid_t pid = fork();
    if (pid > 0) {
        printf("XXX =%s=%p=\n", XXX, XXX);
        while (1);
    } else {
        for (unsigned long i = 0; i < sizeof(args) / sizeof(*args); i++) {
            printf("======args==%s==\n", args[i]);
        }

        printf("XXX =%s=%p=\n", XXX, XXX);

    }
}

char **testXX(int size) {
    char **xx = (char **) malloc(sizeof(char *) * size);
//    char **tmp = xx;
    for (int i = 0; i < size; ++i) {
        *(xx+i) = (char *)malloc(sizeof(char) * size);
        strcpy(*(xx + i), "hell0ksdjhglkdfghkldfjhkdfjhkl");
    }
    return xx;
}

void test() {

    char *a;
    int bb;

//   *hello = "xx";
    char *tmp[] = {"xx", NULL};
    hello = tmp;

    printf("======%d====%p\n", a, a);
    printf("======%d====%p\n", bb, bb);
}
