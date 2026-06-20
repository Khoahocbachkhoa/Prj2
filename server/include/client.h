#ifndef CLIENT_H
#define CLIENT_H

typedef enum {
    ROLE_EDITOR,
    ROLE_VIEWER
} share_role_t;

typedef struct {
    int logged_in;
    int user_id;
    char username[64];
    
    long current_folder_id; // Id thu muc hien tai
    char cwd[256]; // Thu muc lam viec hien tai

    int in_sharing_mode; // = 1 neu dang o trong folder duoc chia se voi toi
    long share_root_folder_id; // Thư mục gốc của phân quyền
    long old_folder_id; // Thu muc truoc khi kia khi dang khong o trong sharing mode
    char share_cwd[256]; // Thu muc hien tai khi dang o trong che do chia se
} session_t;

// Xử lý request của client
void handle_client(int clientfd);

#endif