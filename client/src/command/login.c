#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/security.h"
#include "../../include/state.h"

void cmd_login(ParsedCommand *cmd) {
    if (cmd->argc != 3) {
        printf("Usage: login --user <username>\n");
        return;
    }

    // kiểm tra option
    if (strcmp(cmd->argv[1], "--user") != 0) {
        printf("Error: unknown option '%s'\n", cmd->argv[1]);
        return;
    }

    char *username = cmd->argv[2];
    char password[64]; 
    char req[256];
    char res[256];
    int code;
    char message[256];

    printf("Enter your password: ");
    read_password(password, sizeof(password));

    // Gửi yêu cầu đăng nhập tới server
    snprintf(req, sizeof(req), "LOGIN %s %s\r\n", username, password);
    net_send(state->sockfd, req, strlen(req), 0);

    int ret = net_recv(state->sockfd, res, sizeof(res), 0);
    if (ret == 0) {
        printf("Error: server closed!\n");
        exit(EXIT_FAILURE);
    }

    // Phân tích mã phản hồi
    sscanf(res, "%d %s\r\n", &code, message);
    
    if (code == 200) {
        printf("Login success!\n");
        state->is_logged_in = true;
        strcpy(state->username, username);
        strcpy(state->currentworkspace, "/");
    } else if (code == 401) {
        printf("Error: wrong username or password. Please try again!\n");
    } else if (code == 402) {
        printf("You are aready login! If you want to login to another account, please logout\n");
    } else if (code == 400) {
        printf("Error: bad request!\n");
    } else {
        printf("Error: unknown server errror!\n");
    }

    memset(password, 0, sizeof(password));
    return;
}