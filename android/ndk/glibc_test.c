//
// Created by hello on 2020/6/13.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define __USE_GNU

void strchrs();

void malloc_test();

int main(void) {
    printf("glibc_test\n");

    // test malloc realloc free
    malloc_test();


    // test strchr strrchr strchrnul
    strchrs();
}

void malloc_test() {
    void *pVoid = calloc(sizeof(int), 10);
    printf("calloc: %lu - %p\n", sizeof(int), pVoid);
    free(pVoid);
    char *tmp = (char *) malloc(sizeof(char) * 10);
    printf("malloc: %lu - %p size: %lu\n", sizeof(tmp), tmp, strlen(tmp));
    *(tmp + 100) = 'a';
    tmp = realloc(tmp, sizeof(char) * 10 * 10);
    printf("remalloc: %lu - %p size: %lu\n", sizeof(tmp), tmp, strlen(tmp));

    free(tmp);
}

const char *strchrnul(const char *str, char c) {
    char *x = strchr(str, c);
    if (x) {
        return x;
    }
    return str + strlen(str);
}

void strchrs() {

    char *string = "abacgdedfghcjk";

    printf("strchrs: string -> %s\n", string);
    // not found
    printf("strchrs: strchr %c - %s\n", '0', strchr(string, '0'));
    printf("strchrs: strchr %c - %s\n", 'm', strrchr(string, 'm'));
    printf("strchrs: strchrnul %c - %s\n", 'x', strchrnul(string, 'x'));

    // will found
    printf("strchrs: strchr %c - %s\n", 'b', strchr(string, 'b'));
    printf("strchrs: strchr %c - %s\n", 'c', strrchr(string, 'c'));
    printf("strchrs: strchrnul %c - %s\n", 'g', strchrnul(string, 'g'));

}
