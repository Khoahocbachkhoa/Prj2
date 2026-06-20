#include <stdio.h>
#include <stdlib.h>

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