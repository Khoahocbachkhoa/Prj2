#ifndef DB_FILE_H
#define DB_FILE_H

#include "database.h"
#include "db_folder.h"

// Liệt kê các file có trong thư mục có folder_id
db_errror_code db_file_list(int folder_id, Entry *entries, size_t *max_entries_len);

#endif