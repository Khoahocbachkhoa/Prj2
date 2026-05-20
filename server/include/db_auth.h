#ifndef DB_AUTH_H
#define DB_AUTH_H

typedef enum {
    DB_AUTH_OK = 0,
    DB_AUTH_ERROR,
    DB_AUTH_INVALID_ARGUMENT,
    DB_AUTH_INVALID_CREDENTIALS
} DbAuthStatus;

// Kiểm tra tên đăng nhập + mật khẩu
DbAuthStatus db_check_login(const char *username, const char *password, int *id);

#endif 