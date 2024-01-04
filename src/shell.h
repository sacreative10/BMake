
#ifndef BMAKE_SHELL_H
#define BMAKE_SHELL_H

#include <stdbool.h>
#include <stdio.h>

int get_popen (FILE **pipe, char *cmd, char *get_error_prompt);

int close_popen (FILE **pipe);

#endif
