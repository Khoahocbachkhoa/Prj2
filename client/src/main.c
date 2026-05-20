#include "../include/app.h"

int main() {
    init();

    while (1) {
        shell_print_prompt();

        char *line = shell_read_line();
        if (!line || line[0] == '\0') continue;

        shell_excute(line);
    }

    return 0;
}