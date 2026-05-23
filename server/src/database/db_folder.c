#include <stdio.h>
#include <stdlib.h>

#include "../../include/db_pool.h"
#include "../../include/db_folder.h"
#include "../../include/db_user.h"

int db_folder_create_root(char *username) {
    int id;
    char id_str[32];
    // Tìm kiếm id của user có username
    int ret = db_user_find_id_by_username(username, &id);

    if (ret == DB_USER_ERROR) {
        fprintf(stderr, "create root folder error!\n");
        return 1;
    } else if (ret == DB_USER_NOT_FOUND) {
        fprintf(stderr, "create root folder: username not found!\n");
        return 1;
    }

    // tạo thư mục gốc cho user có id
    PGconn *conn = db_acquire();

    if (conn == NULL) {
        fprintf(stderr, "create root folder: pool exhausted\n");
        return 1;
    }

    const char *query = 
        "INSERT INTO folders "
        "(owner_id, parent_id, name, created_by, is_root) "
        "VALUES ($1, NULL, '/', $1, TRUE);";

    const char *params[1];
    snprintf(id_str, sizeof(id_str), "%d", id);
    params[0] = id_str;

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "create root folder query error: %s\n", PQerrorMessage(conn));

        PQclear(res);
        db_release(conn);
        return 1;
    }

    PQclear(res);
    db_release(conn);

    return 0;
}