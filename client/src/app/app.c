#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../include/app.h"
#include "../../include/server.h"
#include "../../include/state.h"
#include "../../include/parser.h"
#include "../../include/command.h"

void init(int argc, char *argv[]) {
    // parse ip and server port from argv
    char ip[32];
    int port = atoi(argv[2]);

    if (strcmp(argv[1], "localhost") == 0)
        strcpy(ip, "127.0.0.1");
    else
        strcpy(ip, argv[2]);

    // connect to server
    int sockfd = connect_to_server(ip, port);
    
    init_state(state, sockfd);
    printf("Welcome to client shell!\nType help to information!\nType quit to quit\n");
}

void shell_print_prompt() {
    printf("%s:%s$ ", state->username, state->currentworkspace);
    fflush(stdout);
}

char *shell_read_line() {
    static char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return NULL;
    } 

    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') {
        buf[len-1] = '\0';
    }

    return buf;
}

void shell_excute(char *line) {
    ParsedCommand cmd;

    if (!parseLine(line, &cmd))
        return;

    command_dispatch(&cmd);
}

void app_shutdown() {
    close(state->sockfd);
}