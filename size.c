//
// Created by hello on 2018/12/14.
//

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    printf("short int: %ld\n", sizeof(short int));
    printf("int: %ld\n", sizeof(int));
    char buf[1024];
    printf("buf[1024]: %ld\n", sizeof(buf));
    printf("buf[1024]: %ld\n", strlen(buf));
    
    char *ss = "abcdefjhijk";
    printf("ss: %ld\n", sizeof(ss));
    printf("ss: %ld\n", strlen(ss));
    printf("\\0 => strlen: %ld\tsizeof: %ld\n", strlen("\0"), sizeof("\0"));
    printf("abcdefghijklmn strlen=>%ld\tsizeof=>%ld\n", strlen("abcdefghijklmn"), sizeof("abcdefghijklmn"));
}

