//
// Created by Knight on 2019/8/28.
//
#include <stdio.h>

int main() {
    char a = 0, b = 0;
    int *p = (int *) &b;
    *p = 0x12345678;
    printf("%x-%x\n", a, b);

    printf("===%ld=%ld=\n", sizeof(int), sizeof(unsigned int));
    return 0;
}