#include "../include/app.h"

int main() {
    init();

    while (1) {
        shell_print_prompt();

        char *line = shell_read_line();
        if (!line) continue;

        shell_excute(line);
    }

    shutdown();
    return 1;
}
