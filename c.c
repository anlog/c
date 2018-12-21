//
// Created by Knight on 2018-12-21.
//

#include <stdio.h>

enum {
    A = '-',
    B = 0x5f,
    C = 055,
};

void main(int argc, char **argv) {

    printf("##%c%c%c##\n", A, B, C);
}