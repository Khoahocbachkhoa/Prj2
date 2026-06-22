#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/app.h"
#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/state.h"

void cmd_upload(ParsedCommand *cmd) {
    if (cmd->argc == 1) {
        printf("Usage: put --path path_to_file\n");
        return;
    }

    
}

void cmd_download(ParsedCommand *cmd) {

}

void cmd_download_shared(ParsedCommand *cmd) {
    
}