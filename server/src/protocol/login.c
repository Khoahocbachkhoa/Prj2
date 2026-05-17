#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#include "../../include/protocols.h"
#include "../../include/transport.h"
#include "../../include/client.h"
#include "../../include/db_user.h"

void handle_login(int clientfd, const char *req, session_t *session) {
    char cmd[16];
    char username[64];
    char password[64];
    char res[256];
    int *id = (int*)malloc(sizeof(int));

    if (id == NULL) {
        snprintf(res, sizeof(res), "500 ERROR_SERVER\r\n");
        net_send(clientfd, res, strlen(res), 0);
        return;
    }

    int ret = sscanf(req, "%s %s %s\r\n", cmd, username, password);
    if (ret != 3) {
        snprintf(res, sizeof(res), "400 BAD_REQUEST\r\n");
        net_send(clientfd, res, strlen(res), 0);
        return;
    }

    if (session->logged_in) {
        snprintf(res, sizeof(res), "402 ALREADY_LOGIN\r\n");
        net_send(clientfd, res, strlen(res), 0);
        return;
    }

    ret = db_check_login(username, password, id);
    if (ret == DB_USER_ERROR) {
        snprintf(res, sizeof(res), "500 ERROR_SERVER\r\n");
        net_send(clientfd, res, strlen(res), 0);
        return;
    } else if (ret == DB_USER_INVALID_CREDENTIALS) {
        snprintf(res, sizeof(res), "401 INVALID_CREDENTIALS\r\n");
        net_send(clientfd, res, strlen(res), 0);
        return;
    }

    // Login oke
    session->logged_in = 1;
    strncpy(session->username, username, sizeof(session->username) - 1);
    session->username[sizeof(session->username) - 1] = '\0';
    session->user_id = *id;

    if (ret == DB_USER_OK) {
        snprintf(res, sizeof(res), "200 LOGIN_SUCCESS\r\n");
        net_send(clientfd, res, strlen(res), 0);
    }
}