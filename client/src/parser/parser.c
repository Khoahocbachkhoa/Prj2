#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/parser.h"

int parseLine(char *line, ParsedCommand *cmd) {
    cmd->argc = 0;
    char *token = strtok(line, " \t\n");

    while (token && cmd->argc < MAX_ARGS) {
        cmd->argv[cmd->argc++] = token;
        token = strtok(NULL, " \t\n");
    }

    return cmd->argc;
}