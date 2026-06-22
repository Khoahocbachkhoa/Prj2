#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/app.h"
#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/state.h"


void cmd_pwd(ParsedCommand *cmd) {
    if (cmd->argc != 1) {
        printf("Usage: pwd\n");
        return;
    }

    send_command(state->sockfd, "PWD\r\n");
}

void cmd_list(ParsedCommand *cmd) {
    if (cmd->argc != 1) {
        printf("Usage: list\n");
        return;
    }

    send_command(state->sockfd, "LIST\r\n");
}

void cmd_mkdir(ParsedCommand *cmd) {
    if (cmd->argc != 2) {
        printf("Usage: mkdir <folder_name>\n(Only support one dir per command!)\n");
        return;
    }


}

void cmd_cd(ParsedCommand *cmd) {

}

void cmd_delete(ParsedCommand *cmd) {

}

void cmd_rmdir(ParsedCommand *cmd) {

}

void cmd_rename(ParsedCommand *cmd) {

}