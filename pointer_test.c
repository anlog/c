//
// Created by Knight on 2019/8/26.
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
//    char *str = "hello";
//
//    printf("==%c=\n", str[0]);
//    return 1;

    char *args[] = {"ls", "-al", NULL};
    char **args_p = args;
    pid_t i = fork();
    if (i > 0) {
        while (1);
    } else {
        int ret = execvp(*args_p, args_p);
        if (ret) {
            perror("execvp");
        }
    }
    return 1;

    char *pointer = "hello world!";

    for (;;) {
        if (*pointer == '\0') {
            break;
        }

        printf("==%c=%d=%p=\n", *pointer, *pointer, pointer++);
    }

    char *array[10];
    char **array_p = array;


    char *tmp[] = {"ls", "-al"};

//    printf("=====%c=\n", *tmp);
//    return 1;
    printf("\n\n\n");
    int count = 0;
    char* xx = "hello";
    *array_p++ = xx;
    for (;;) {
        if (count > 10 - 1) {
            break;
        }
        printf("=tmp==%s=\n", tmp[0]);
        *array_p++ = tmp[count];
        printf("==%s==%d==\n", *(array_p - 1), count++);
    }

    printf("==pointer: %p -- %p\n", xx, *array);
    printf("==pointer: %p -- %p\n", *tmp, *(array+1));

    printf("===========%s=======\n%s\n", xx, *(array + 1));

    printf("xxxxxxxx%ldx%ldx\n", sizeof(array), sizeof(*array));

}
