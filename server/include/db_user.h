#ifndef DB_USER_H
#define DB_USER_H

typedef enum {
    DB_USER_OK = 0,
    DB_USER_ERROR,
    DB_USER_EXISTS,
    DB_USER_NOT_FOUND,
    DB_USER_INVALID_ARGUMENT,
    DB_USER_INVALID_CREDENTIALS
} DbUserStatus;

// Kiểm tra user có tồn tại hay chưa
DbUserStatus db_user_exists(const char *username);

// Tạo user mới
DbUserStatus db_user_insert(const char *username, const char *password);

#endif