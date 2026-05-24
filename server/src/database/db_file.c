#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/db_pool.h"
#include "../../include/db_folder.h"
#include "../../include/db_files.h"
#include "../../include/db_user.h"
#include "../../include/database.h"

db_errror_code db_file_list(int folder_id, Entry *entries, size_t *maxlen) {
    if (entries == NULL) {
        return ERR_INVALID_ARGUMENT;
    }

    // int ret = db_folder_check_status(folder_id);
    // if (ret != OK) {
    //     return ret;
    // }

    PGconn *conn = db_acquire();
    if (conn == NULL) {
        fprintf(stderr, "List files: Db exhausted error\n");
        return ERR;
    }

    const char *query = "select f.id, f.filename, u.username as ownername, f.updated_at "
        "from files f join users u on f.owner_id = u.id "
        "where f.folder_id = $1 and f.deleted_at is NULL "
        "order by f.filename;";

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
    if ((size_t)rows > *maxlen) rows = *maxlen;

    for (int i = 0; i < rows; ++i) {
        entries[i].type = ENTRY_FILE;
    
        entries[i].id = atol(PQgetvalue(res, i, 0));

        snprintf(entries[i].name, sizeof(entries[i].name), "%s", PQgetvalue(res, i, 1));

        snprintf(entries[i].owner, sizeof(entries[i].owner), "%s", PQgetvalue(res, i, 2));

        snprintf(entries[i].updated_at, sizeof(entries[i].updated_at), "%s", PQgetvalue(res, i, 3));
    }

    *maxlen = (size_t)rows;
    PQclear(res);
    db_release(conn);

    return OK;
}