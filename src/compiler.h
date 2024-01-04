
#ifndef BMAKE_COMPILER_H
#define BMAKE_COMPILER_H

#include "project_files.h"
#include "shell.h"
#include <stdio.h>

int compile_file (char *file, char **objPath);
int link_executable (char **objPath, char **executable_name);
int create_obj_folder (char *path);
#endif // !BMAKE_COMPILER_H
