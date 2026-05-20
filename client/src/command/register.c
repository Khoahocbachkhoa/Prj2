#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/security.h"
#include "../../include/state.h"

void cmd_register(ParsedCommand *cmd) {
    if (cmd->argc != 3) {
        printf("Usage: register --user <username>\n");
        return;
    }

    // kiểm tra option
    if (strcmp(cmd->argv[1], "--user") != 0) {
        printf("Error: unknown option '%s'\n", cmd->argv[1]);
        return;
    }

    char *username = cmd->argv[2];
    char password[64];
    char buf[64];
    char req[256];
    char res[256];
    int status_code;
    char message[256];
    
    printf("Enter your password: ");
    read_password(password, sizeof(password));
    printf("Confirm your password: ");
    read_password(buf, sizeof(buf));

    if (strcmp(password, buf) != 0) {
        printf("Error: password dont match!\n");
        return;
    }

    // Gửi yêu cầu đăng ký tới server
    snprintf(req, sizeof(req), "REGISTER %s %s\r\n", username, password);
    net_send(state->sockfd, req, strlen(req), 0);
    // Nhận phản hồi từ server
    int ret = net_recv(state->sockfd, res, sizeof(res), 0);

    // Nếu server bị crash -> thoát khỏi chương trình luôn
    if (ret == 0) {
        printf("Error: server closed!\n");
        exit(EXIT_FAILURE);
    }

    // Phân tích phản hồi
    sscanf(res, "%d %s\r\n", &status_code, message);

    if (status_code == 200) {
        printf("Register successfully!\n");
    } else if (status_code == 409) {
        printf("User already exist!\n");
    } else if (status_code == 400) {
        printf("Error: bad request!\n");
    } else if (status_code == 422) {
        printf("Password too weak!\n");
    } else {
        printf("Error: unknown server error\n");
    }

    memset(password, 0, sizeof(password));
    memset(buf, 0, sizeof(buf));

    return;
}