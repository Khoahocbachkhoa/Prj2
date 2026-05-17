#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/db_pool.h"
#include "../../include/db_user.h"

// Kiểm tra sự tồn tại của user cũ
DbUserStatus db_user_exists(const char *username) {
    if (username == NULL)
        return DB_USER_INVALID_ARGUMENT;

    PGconn *conn = db_acquire();
    if (conn == NULL) {
        fprintf(stderr, "db_user_exists: pool exhausted\n");
        return DB_USER_ERROR;
    }

    const char *query = "select count(*) from users where username = $1;";
    const char *params[1];
    params[0] = username;

    // Thực thi truy vấn
    PGresult *res = PQexecParams(conn, 
        query, 
        1, // số tham số
        NULL,
        params,
        NULL,
        NULL,
        0  // Nhận kết quả dạng text
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "query errror!");
        PQclear(res);
        db_release(conn);
        return DB_USER_ERROR;
    } 

    // Lấy kết quả trả về
    char *count_str = PQgetvalue(res, 0, 0);
    int cnt = atoi(count_str);

    PQclear(res);
    db_release(conn);

    return (cnt == 0) ? DB_USER_NOT_FOUND : DB_USER_EXISTS;
}

// Tạo 1 user mới
DbUserStatus db_insert_user(const char *username, const char *password) {
    if (username == NULL || password == NULL) {
        return DB_USER_INVALID_ARGUMENT;
    }

    PGconn *conn = db_acquire();
    if (conn == NULL) {
        fprintf(stderr, "db_user_exists: pool exhausted\n");
        return DB_USER_ERROR;
    }

    const char *query = "insert into users(username, password) "
                        "values ($1, $2);";
                    
    const char *params[2];
    params[0] = username;
    params[1] = password;

    PGresult *res = PQexecParams(conn, query, 2, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Lỗi truy vấn(db_insert_user)!");
        PQclear(res);
        return DB_USER_ERROR;
    }

    PQclear(res);
    return DB_USER_OK;
}