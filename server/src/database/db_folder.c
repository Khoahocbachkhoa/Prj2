#include <stdio.h>
#include <stdlib.h>

#include "../../include/db_pool.h"
#include "../../include/db_folder.h"
#include "../../include/db_user.h"
#include "../../include/database.h"

db_errror_code db_folder_create_root(char *username) {
    int id;
    char id_str[32];
    // Tìm kiếm id của user có username
    int ret = db_user_find_id_by_username(username, &id);

    if (ret == ERR) {
        fprintf(stderr, "create root folder error!\n");
        return ERR;
    } else if (ret == DB_USER_NOT_FOUND) {
        fprintf(stderr, "create root folder: username not found!\n");
        return ERR;
    }

    // tạo thư mục gốc cho user có id
    PGconn *conn = db_acquire();

    if (conn == NULL) {
        fprintf(stderr, "create root folder: pool exhausted\n");
        return ERR;
    }

    const char *query = 
        "INSERT INTO folders "
        "(owner_id, parent_id, name) "
        "VALUES ($1, NULL, '/');";

    const char *params[1];
    snprintf(id_str, sizeof(id_str), "%d", id);
    params[0] = id_str;

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "create root folder query error: %s\n", PQerrorMessage(conn));

        PQclear(res);
        db_release(conn);
        return ERR;
    }

    PQclear(res);
    db_release(conn);

    return OK;
}

db_errror_code db_folder_find_root(int user_id, int *root_id) {
    PGconn *conn = db_acquire();

    if (conn == NULL) {
        fprintf(stderr, "find root folder: pool exhausted\n");
        return ERR;
    }

    const char *query = "select id from folders where owner_id = $1 and parent_id is NULL;";
    const char *params[1];
    char id_str[32];
    snprintf(id_str, sizeof(id_str), "%d", user_id);
    params[0] = id_str;

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Fint root folder error: %s\n", PQerrorMessage(conn));

        PQclear(res);
        db_release(conn);
        return ERR;
    }

    if (PQntuples(res) == 0) {
        fprintf(stderr, "Find roor folder: user_id not found!\n");
        PQclear(res);
        db_release(conn);

        return DB_USER_NOT_FOUND;
    }

    // Lay root folder id
    *root_id = atoi(PQgetvalue(conn, 0, 0));

    PQclear(res);
    db_release(conn);

    return OK;
}