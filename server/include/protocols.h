#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include "client.h"

// Xử lý logic đăng ký
void handle_register(int clientfd, const char *req);

// Xử lý logic đăng nhập
void handle_login(int clientfd, const char *req, session_t *session);

// Xử lý đăng xuất
void handle_logout(int clientfd, const char *req, session_t *session);

// Xử lý pwd
void handle_pwd(int clientfd, const char *req, session_t *session);

#endif