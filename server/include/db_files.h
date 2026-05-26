#ifndef DB_FILE_H
#define DB_FILE_H

#include "database.h"
#include "db_folder.h"
#include "client.h"

// Liệt kê các file có trong thư mục có folder_id
db_errror_code db_file_list(int folder_id, Entry *entries, size_t *max_entries_len);

// Kiểm tra một tên file đã tồn tại trong thư mục hay chưa
db_errror_code db_file_exists(int fid, const char *fname);

// Thêm một meta data
db_errror_code db_file_insert(char *fname, char *storagekey, int fsize, session_t *session);

#endif