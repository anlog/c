//
// Created by hello on 2018/12/16.
//

#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sock_addr;
    bzero(&sock_addr, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr.s_addr) < 0) {
        perror("inet_pton");
        return 0;
    }
    sock_addr.sin_port = htons(7);

    if (connect(sock, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) {
        perror("connect");
        return 0;
    }
    char buf[1024];
    ssize_t m, n;
    for (;;) {
        if (fgets(buf, sizeof(buf), stdin) && strlen(buf) == 0) {
            printf("continue\n");
            continue;
        }
//        printf("=====> %d", strncmp("q", buf, 1));
        if (0 == strncmp("q", buf, 1)) {
            break;
        }
        if (write(sock, buf, strlen(buf)) <= 0) {
            perror("write");
            return 0;
        }
        printf("write: %s@%ld\n", buf, strlen(buf));

        if ((n = read(sock, buf, sizeof(buf))) == 0) {
            break;
        }
        printf("read: %s@%ld\n", buf, n);
    }
    close(sock);
}
