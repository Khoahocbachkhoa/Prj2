#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

typedef struct {
    bool is_logged_in;
    
    char username[64];
    char currentworkspace[64];

    int sockfd;
} ClientState;

extern ClientState *state;

void init_state(ClientState *state, int fd);

#endif