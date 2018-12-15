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
    
    char *ss = "abcde";
    printf("buf[1024]: %ld\n", sizeof(ss));
    printf("buf[1024]: %ld\n", strlen(ss));


}

