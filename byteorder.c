//
// Created by hello on 2018/12/16.
//

#include <stdio.h>

int main() {
    union {
        short s;
        char ss[sizeof(short)]
    } un;

    un.s = 0x0102;
    if (un.ss[0] == 1 && un.ss[1] == 2) {
        printf("big-endian");
    } else if (un.ss[0] == 2 && un.ss[1] == 1) {
        printf("little-endian");
    } else {
        printf("unknown");
    }
}

