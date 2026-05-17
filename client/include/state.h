#ifndef STATE_H
#define STATE_H

typedef struct {
    int is_logged_in;
    char username[64];
} ClientState;

extern ClientState g_state;

void init_state();

#endif