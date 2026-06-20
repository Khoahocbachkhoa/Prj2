#ifndef DB_SHARING_H
#define DB_SHARING_H

#include "database.h"

// cấp quyền truy cập file cho 1 user
db_errror_code db_sharing_grant_file_access(int file_id, int user_id);

#endif