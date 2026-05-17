#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../include/client.h"
#include "../../include/protocols.h"
#include "../../include/transport.h"
#include "../../include/database.h"

void handle_client(int clientfd) {
    char buf[BUFSIZ];
    char cmd[16];

    // Nhận request từ người dùng và phản hồi
    while (1) {
        memset(buf, 0, BUFSIZ);

        int n = net_recv(clientfd, buf, BUFSIZ, 0);

        // client disconnected
        if (n <= 0) break;

        buf[n] = '\0';
        sscanf(buf, "%s", cmd);

        if (strcmp(cmd, "REGISTER") == 0) {
            handle_register(clientfd, buf);
        } else if (strcmp(cmd, "LOGIN") == 0) {
            handle_login(clientfd, buf);
        } else {

        }
    }
}