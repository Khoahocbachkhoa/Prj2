#include <stdlib.h>

#include "../../include/app.h"
#include "../../include/command.h"
#include "../../include/parser.h"
#include "../../include/transport.h"
#include "../../include/security.h"
#include "../../include/state.h"

void cmd_exit(ParsedCommand *cmd) {
    shutdown();
    exit(EXIT_SUCCESS);
}