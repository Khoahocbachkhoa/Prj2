#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../../include/state.h"
#include "../../include/app.h"

ClientState global_state;
ClientState *state = &global_state;

void init_state(ClientState *state) {
    snprintf(state->username, sizeof(state->username), "guest");
    snprintf(state->currentworkspace, sizeof(state->currentworkspace), "~");
    state->is_logged_in = false;

    // Connect to server as guest
    struct sockaddr_in servaddr;

    if ((state->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Cannot create socket!\n");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVADDR, &servaddr.sin_addr);

    if (connect(state->sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "Cannot connect to server!\n");
        exit(EXIT_FAILURE);
    }
}