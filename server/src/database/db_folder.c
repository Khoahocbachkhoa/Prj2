#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

db_errror_code db_folder_find_root(int user_id, long *root_id) {
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
    *root_id = atoi(PQgetvalue(res, 0, 0));

    PQclear(res);
    db_release(conn);

    return OK;
}

db_errror_code db_folder_check_status(int folder_id) {
    PGconn *conn = db_acquire();

    if (conn == NULL) {
        return ERR;
    }

    const char *query = "select deleted_at from folders where id = $1";
    const char *params[1];
    char id_str[32];
    snprintf(id_str, sizeof(id_str), "%d", folder_id);
    params[0] = id_str;

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Check status folder error: %s\n", PQerrorMessage(conn));
        PQclear(res);
        db_release(conn);
        return ERR;
    }

    if (PQntuples(res) == 0) {
        fprintf(stderr, "Check status folder: folder not found\n");
        PQclear(res);
        db_release(conn);
        return DB_FOLDER_NOT_FOUND;
    }

    int ret;
    if (!PQgetisnull(res, 0, 0)) {
        ret = DB_FOLDER_DELETED;
    } else {
        ret = OK;
    }

    PQclear(res);
    db_release(conn);

    return ret;
}

// Liệt kê nội dung của thư mục có folder_id
db_errror_code db_folder_list(int folder_id, Entry *entries, size_t *maxlen) {
    if (entries == NULL) {
        return ERR_INVALID_ARGUMENT;
    }

    // int ret = db_folder_check_status(folder_id);
    // if (ret != OK) {
    //     return ret;
    // }

    // Liệt kê các folder trước
    PGconn *conn = db_acquire();
    
    if (conn == NULL) {
        fprintf(stderr, "List : Db exhausted error\n");
        return ERR;
    }

    const char *query = "select f.id, f.name, u.username as ownername, f.updated_at "
        "from folders f join users u on f.owner_id = u.id "
        "where f.parent_id = $1 and f.deleted_at is NULL "
        "order by f.name;";

    const char *params[1];
    char id_str[32];
    snprintf(id_str, sizeof(id_str), "%d", folder_id);
    params[0] = id_str;

    PGresult *res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error: %s", PQerrorMessage(conn));
        PQclear(res);
        db_release(conn);
        return ERR;
    }

    int rows = PQntuples(res);
    if (rows < *maxlen) rows = *maxlen;

    for (int i = 0; i < rows; ++i) {
        entries[i].type = ENTRY_FOLDER;
    
        entries[i].id = atol(PQgetvalue(res, i, 0));

        snprintf(entries[i].name, sizeof(entries[i].name), "%s", PQgetvalue(res, i, 1));

        snprintf(entries[i].owner, sizeof(entries[i].owner), "%s", PQgetvalue(res, i, 2));

        snprintf(entries[i].updated_at, sizeof(entries[i].updated_at), "%s", PQgetvalue(res, i, 3));
    }

    *maxlen = rows;
    PQclear(res);
    db_release(conn);

    return OK;
}
