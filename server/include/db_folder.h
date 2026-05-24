#ifndef DB_FOLDER_H
#define DB_FOLDER_H

#include "database.h"
#include <time.h>

#define MAXENTRYSIZE 128

typedef enum {
    ENTRY_FILE,
    ENTRY_FOLDER
} EntryType;

typedef struct {
    long id;

    EntryType type;

    char name[256];

    char owner[64];

    char updated_at[128];
} Entry;

// Tạo thư mục root khi tạo user
db_errror_code db_folder_create_root(char *username);

// Tìm id của thư mục gốc của user có thư mục gốc
db_errror_code db_folder_find_root(int user_id, long *root_id);

// Liệt kê nội dung có trong thư mục đó
db_errror_code db_folder_list(int folder_id, Entry *entries, size_t *max_entries_len);

// Kiểm tra trạng thái của một folder (khả dụng, bị đánh dấu là xóa, không tồn tại trong db nữa)
db_errror_code db_folder_check_status(int folder_id);

#endif
