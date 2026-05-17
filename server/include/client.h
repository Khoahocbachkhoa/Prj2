#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
    int logged_in;
    int user_id;
    char username[64];
} session_t;

// Xử lý request của client
void handle_client(int clientfd);

#endif