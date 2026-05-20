#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/command.h"
#include "../../include/parser.h"

static Command commands[] =
{
    {"login",  cmd_login},
    {"logout", cmd_logout},
    {"exit",   cmd_exit},
    {"quit",   cmd_exit},
    {"register", cmd_register}
};

void command_dispatch(ParsedCommand *cmd) {
    size_t cnt = sizeof(commands) / sizeof(commands[0]);

    // look up for handler
    for (size_t i = 0; i < cnt; ++i) {
        if (strcmp(cmd->argv[0], commands[i].name) == 0) {
            // Gọi handler
            commands[i].handler(cmd);
            return;
        }
    }

    // Không tìm thấy command!
    printf("Error: unknown command '%s'\n", cmd->argv[0]);
}