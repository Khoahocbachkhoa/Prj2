#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/db_pool.h"
#include "../../include/database.h"
#include "../../include/db_sharing.h"

db_errror_code db_sharing_grant_file_access(int file_id, int user_id) {
    PGconn *conn = db_acquire();
    if (conn == NULL) {
        fprintf(stderr, "File access: Db exhausted error\n");
        return ERR;
    }

    const char *query =
        "INSERT INTO file_permissions "
        "(file_id, user_id) "
        "VALUES ($1, $2)";

    char file_id_str[16];
    char user_id_str[16];

    snprintf(file_id_str, sizeof(file_id_str), "%d", file_id);
    snprintf(user_id_str, sizeof(user_id_str), "%d", user_id);

    const char *params[2] = {
        file_id_str,
        user_id_str
    };

    PGresult *res = PQexecParams(
        conn,
        query,
        2,         
        NULL,   
        params,
        NULL, 
        NULL,    
        0
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr,
                "Failed to grant file access: %s\n",
                PQerrorMessage(conn));

        PQclear(res);
        db_release(conn);
        return ERR;
    }

    PQclear(res);
    db_release(conn);

    return OK;
}

// hủy quyền chia sẻ file cho 1 user
db_errror_code db_sharing_revoke_file_access(int file_id, int user_id) {
    PGconn *conn = db_acquire();
    if (conn == NULL) {
        fprintf(stderr, "File access: Db exhausted error\n");
        return ERR;
    }

    const char *query =
        "DELETE FROM file_permissions "
        "WHERE file_id = $1 AND user_id = $2";

    char file_id_str[16];
    char user_id_str[16];

    snprintf(file_id_str, sizeof(file_id_str), "%d", file_id);
    snprintf(user_id_str, sizeof(user_id_str), "%d", user_id);

    const char *params[2] = {
        file_id_str,
        user_id_str
    };

    PGresult *res = PQexecParams(
        conn,
        query,
        2,
        NULL,
        params,
        NULL,
        NULL,
        0
    );

    char *affected = PQcmdTuples(res);

    if (affected != NULL && strcmp(affected, "0") == 0) {
        fprintf(stderr,
                "No permission found for file_id=%d user_id=%d\n",
                file_id, user_id);

        PQclear(res);
        db_release(conn);
        return DB_SHARING_NOT_FOUND;
    }

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr,
                "Failed to revoke file access: %s\n",
                PQerrorMessage(conn));

        PQclear(res);
        db_release(conn);
        return ERR;
    }

    PQclear(res);
    db_release(conn);

    return OK;
}

db_errror_code db_sharing_list_users_shared(int file_id, char **users, size_t *users_size) {
    PGconn *conn = db_acquire();
    if (conn == NULL) {
        fprintf(stderr, "DB exhausted error\n");
        return ERR;
    }

    const char *query =
        "SELECT u.username "
        "FROM file_permissions fp "
        "JOIN users u ON fp.user_id = u.id "
        "WHERE fp.file_id = $1 "
        "ORDER BY u.username";

    char file_id_str[16];
    snprintf(file_id_str, sizeof(file_id_str), "%d", file_id);

    const char *params[1] = { file_id_str };

    PGresult *res = PQexecParams(
        conn,
        query,
        1,
        NULL,
        params,
        NULL,
        NULL,
        0
    );

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr,
                "Failed to list shared users: %s\n",
                PQerrorMessage(conn));

        PQclear(res);
        db_release(conn);
        return ERR;
    }

    int rows = PQntuples(res);

    if (*users_size < rows) {
        // Khong du kich thuoc bo dem
        rows = *users_size;
    }

    *users_size = rows;

    if (rows == 0) {
        PQclear(res);
        db_release(conn);
        return OK;
    }

    for (int i = 0; i < rows; i++) {
        const char *username = PQgetvalue(res, i, 0);

        //users[i] = strdup(username);
        memcpy(users[i], username, 256);
        if (users[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(users[j]);
            }

            PQclear(res);
            db_release(conn);
            return ERR;
        }
    }

    PQclear(res);
    db_release(conn);

    return OK;
}