#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../../include/state.h"
#include "../../include/app.h"
#include "../../include/server.h"

ClientState global_state;
ClientState *state = &global_state;

void init_state(ClientState *state, int fd) {
    snprintf(state->username, sizeof(state->username), "guest");
    snprintf(state->currentworkspace, sizeof(state->currentworkspace), "~");
    state->is_logged_in = false;
    state->sockfd = fd;
}