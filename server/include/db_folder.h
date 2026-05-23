#ifndef DB_AUTH_H
#define DB_AUTH_H

#include "database.h"

// Tạo thư mục root khi tạo user
db_errror_code db_folder_create_root(char *username);

#endif