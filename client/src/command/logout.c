#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/state.h"

void cmd_logout(ParsedCommand *cmd) {
    if (cmd->argc > 1) {
        printf("Usage: logout\n");
        return;
    }

    char req[256];
    char res[256];
    int code;
    char message[256];

    snprintf(req, sizeof(req), "LOGOUT\r\n");
    net_send(state->sockfd, req, strlen(req), 0);
    int ret = net_recv(state->sockfd, res, sizeof(res), 0);

    if (ret == 0) {
        printf("Error: server closed!\n");
        exit(EXIT_FAILURE);
    }

    sscanf(res, "%d %s\r\n", &code, message);
    if (code == 200) {
        printf("Log out success!\n");
        state->is_logged_in = false;
        snprintf(state->username, sizeof(state->username), "guest");
        snprintf(state->currentworkspace, sizeof(state->currentworkspace), "~");
    } else {
        printf("Error: not login yet!\n");
    }
}
