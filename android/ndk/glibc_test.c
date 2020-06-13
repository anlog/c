//
// Created by hello on 2020/6/13.
//
#include <stdio.h>
#include <string.h>
#include <memory.h>

#define __USE_GNU

void strchrs();

int main(void) {
    printf("glibc_test\n");


    // test strchr strrchr strchrnul
    strchrs();
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
