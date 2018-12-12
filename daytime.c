//
// Created by hello on 2018/12/1.
//

#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        perror("usage: xx <ip address>");
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket error");
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    int ret = inet_pton(AF_INET, argv[1], &addr.sin_addr);
    if (ret < 0) {
        perror("inet_pton error");
    }

    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect error");
    }

#define BUF 1024
    char recv[BUF];
    long int n;
    while ((n = read(fd, recv, BUF)) > 0) {
        recv[n] = '\0';
        if (fputs(recv, stdout) == EOF) {
            perror("fputs error");
        }
    }

    if (n < 0) {
        perror("read error");
    }
    exit(0);
}