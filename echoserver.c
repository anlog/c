//
// Created by hello on 2018/12/16.
//

#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int server, client;
    server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr, client_addr;
    long addr_len = sizeof(client_addr);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(7);

    if ((bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)) {
        perror("bind");
        return 0;
    }
    if (listen(server, 10) == -1) {
        perror("listen");
        return 0;
    }

    for (;;) {
        if ((client = accept(server, (struct sockaddr *) &client_addr, &addr_len)) == -1) {
            perror("accept");
            return 0;
        }
        int pid;
        if ((pid = fork()) == 0) { // child
            close(server);
            printf("client: %x:%d <=> %d:%d\n",
                   ntohl(client_addr.sin_addr.s_addr),
                   ntohs(client_addr.sin_port),
                   ntohl(server_addr.sin_addr.s_addr),
                   ntohs(server_addr.sin_port));
            ssize_t m, n;
            char buf[1024];
            for (;;) {
                if ((n = read(client, buf, sizeof(buf))) == 0) {
                    break;
                }
                if ((m = write(client, buf, (size_t) n)) != n) {
                    perror("write");
                } else {
                    printf("write :%s", buf);
                }
            }
            exit(0);
        }
        close(client);
    }


}
