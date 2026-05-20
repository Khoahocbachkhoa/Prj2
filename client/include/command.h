#ifndef COMMAND_H
#define COMMAND_H

#include "parser.h"

typedef void (*CommandHandler)(
    ParsedCommand *cmd
);

typedef struct
{
    const char *name;
    CommandHandler handler;

} Command;

// dispatch parsed command cho một handle
void command_dispatch(ParsedCommand *cmd);

// Các handler
void cmd_register(ParsedCommand *cmd);
void cmd_login(ParsedCommand *cmd);
void cmd_logout(ParsedCommand *cmd);
void cmd_exit(ParsedCommand *cmd);

#endif