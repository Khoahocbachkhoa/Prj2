#ifndef DB_FOLDER_H
#define DB_FOLDER_H

#include "database.h"

// Tạo thư mục root khi tạo user
db_errror_code db_folder_create_root(char *username);

// Tìm id của thư mục gốc của user có thư mục gốc
db_errror_code db_folder_find_root(int user_id, long *root_id); 

#endif