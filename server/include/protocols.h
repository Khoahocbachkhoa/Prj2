#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <libpq-fe.h>

// Xử lý logic đăng ký
void handle_register(int clientfd, const char *req);

// Xử lý logic đăng nhập
void handle_login(int clientfd, const char *req);

#endif