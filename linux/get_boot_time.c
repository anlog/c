//
// Created by dp on 2019/10/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/vfs.h>

void get_boot_time();

void check_proc();

int main() {
    get_boot_time();
    check_proc();
    return 0;
}

void check_proc() {
    struct statfs fs;
    if(statfs("/proc", &fs) < 0) {
        perror("statfs");
    }else {
        printf("statfs: %lx\n", fs.f_type);
    }
}

void get_boot_time() {
    FILE *pFile = fopen("/proc/uptime", "r");
    if (pFile != NULL) {
        char buf[BUFSIZ];
        char *uptime = fgets(buf, BUFSIZ, pFile);
        if(buf == uptime) {
            printf("uptime: %s\n", buf);

            char* useless_buf;
            double d = strtod(buf, &useless_buf);
            printf("str: #%s# - %f\n", useless_buf, d);
            time_t now = time(NULL);
            printf("now: %ld\n", now);
            const time_t boot_time = (time_t)now - d;

            struct tm *pTm = localtime(&boot_time);

            printf("boot_time: %d-%d-%d = %s\n", pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday, asctime(pTm));

            printf("%d days\n",  pTm->tm_mday);
        }
        fclose(pFile);
    }
}
