

#include "project_files.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
get_number_of_source_files (char **path)
{
  FILE *fp;
  char cmd[MAX_STRLEN];
  snprintf (cmd, sizeof (cmd), "find %s -type f -name \\*.c | wc -l", *path);

  if (get_popen (&fp, cmd, NULL) == -1)
    return -1;

  char num[MAX_SOURCE_FILES];
  fgets (num, MAX_SOURCE_FILES, fp);
  if (close_popen (&fp) == -1)
    return -1;

  if (strlen (num) != 0)
    {
      return atoi (num);
    }
  return -1;
}

int
get_source_files (char **path, char filenames[][MAX_STRLEN])
{
  FILE *fp;
  char cmd[MAX_STRLEN];
  snprintf (cmd, sizeof (cmd), "find %s -type f -name \\*c", *path);

  if (get_popen (&fp, cmd, NULL) == -1)
    {
      return -1;
    }

  int i = 0;
  char filename[MAX_STRLEN];
  while (fgets (filename, MAX_STRLEN, fp) != NULL)
    {
      strcpy (filenames[i], filename);
      i++;
    }

  if (close_popen (&fp) == -1)
    {
      return -1;
    }

  return 0;
}
