#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
    int logged_in;
    int user_id;
    char username[64];
    long current_folder_id; // Id thu muc hien tai
    char cwd[256]; // Thu muc lam viec hien tai
} session_t;

// Xử lý request của client
void handle_client(int clientfd);

#endif