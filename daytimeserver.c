//
// Created by hello on 2018/12/15.
//

#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(13);

    if (bind(sock, (const struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return 0;
    }
    if (listen(sock, 20) == -1) {
        perror("listen");
        return 0;
    }

    int client_addr_len = sizeof(client_addr);
    while (1) {
        int client_fd = accept(sock,
                               (struct sockaddr *) &client_addr,
                               (socklen_t *) &client_addr_len);
        if (client_fd < 0) {
            perror("accept");
            return 0;
        }
        time_t tm = time(NULL);
        char *now = ctime(&tm);
        char buf[strlen(now)];
        snprintf(buf, sizeof(buf), "%.24s\r\n", now);
        printf("client_fd: %d\tbuf, %s", client_fd, buf);
        if (write(client_fd, buf, sizeof(buf)) == -1) {
            perror("write");
        } else {
            printf("write #%s#", buf);
        }

        close(client_fd);
    }
}

