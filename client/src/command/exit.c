#include <stdlib.h>

#include "../../include/app.h"
#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/security.h"
#include "../../include/state.h"

void cmd_exit(ParsedCommand *cmd) {
    if (cmd->argc != 1) {
        printf("Error: two many arguments!\n");
        return;
    }
    
    app_shutdown();
    exit(EXIT_SUCCESS);
}