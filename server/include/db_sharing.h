#ifndef DB_SHARING_H
#define DB_SHARING_H

#include "database.h"
#include "db_folder.h"

// cấp quyền truy cập file cho 1 user
db_errror_code db_sharing_grant_file_access(int file_id, int user_id);

// hủy quyền chia sẻ file cho 1 user
db_errror_code db_sharing_revoke_file_access(int file_id, int user_id);

// Xem cac user nao dang co quyen truy cap file
db_errror_code db_sharing_list_users_shared(int file_id, char **users, int *users_size);

// Xem các user nào đang chia sẻ file cho tôi
db_errror_code db_sharing_list_files_shared_with_me(int user_id, Entry *entries, int *len);

#endif