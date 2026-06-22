#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../../include/parser.h"
#include "../../include/util.h"

bool check_folder_name(const char *fname) {
    if (fname == NULL)
        return false;

    size_t len = strlen(fname);

    if (len == 0 || len > 255)
        return false;

    if (strcmp(fname, ".") == 0 ||
        strcmp(fname, "..") == 0)
        return false;

    for (size_t i = 0; i < len; i++) {
        if (fname[i] == '/')
            return false;
    }

    return true;
}