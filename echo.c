//
// Created by hello on 2018/12/16.
//

#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

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
        fgets(buf, sizeof(buf), stdin);
        if (n <= 1) {
            break;
        }
        if (write(sock, buf, sizeof(buf)) <= 0) {
            perror("write");
            return 0;
        }

        if ((n = read(sock, buf, sizeof(buf))) == 0) {
            break;
        }
        printf("read: %s", buf);
    }
    close(sock);
}
