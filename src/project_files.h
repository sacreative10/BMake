#ifndef BMAKE_PROJECT_FILES_H
#define BMAKE_PROJECT_FILES_H

#define MAX_STRLEN 200
#define MAX_SOURCE_FILES 200

int get_number_of_source_files (char **path);
int get_source_files (char **path, char filenames[][MAX_STRLEN]);

#endif // !BMAKE_PROJECT_FILES_H
