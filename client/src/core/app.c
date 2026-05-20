#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../include/app.h"
#include "../../include/state.h"
#include "../../include/parser.h"
#include "../../include/command.h"

static volatile sig_atomic_t g_interrupted = 0;

// Xử lý khi user bấm Ctrl + C
static void handle_sigint(int sig) {
    (void)sig;

    g_interrupted = 1;

    write(STDOUT_FILENO, "\n", 1);
}

void init() {
    init_state(state);
    printf("Welcome to client shell!\n Type help to information!\n Type quit to quit\n");
    signal(SIGINT, handle_sigint); // Xử lý khi người dùng bấm Ctrl + C
}

void shell_print_prompt() {
    printf("%s %s $ ", state->username, state->currentworkspace);
}

char *shell_read_line() {
    static char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));
    g_interrupted = 0; 

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        // Ctrl + C
        if (g_interrupted) {
            clearerr(stdin);
            return NULL;
        }

        // Ctrl + D
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