#include "compiler.h"
#include "project_files.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void
delete_end (char *inp_str)
{
  char *del = &inp_str[strlen (inp_str)];

  while (del > inp_str && *del != '/')
    del--;

  if (*del == '/')
    *del = '\0';

  return;
}

int
compile_file (char *file, char **objPath)
{
  FILE *fp;
  char cmd[MAX_STRLEN];

  // create the object directory (second-level).

  char *temp_ = strdup (file);
  delete_end (temp_);
  char dir[MAX_STRLEN];
  snprintf (dir, MAX_STRLEN, "%s/%s", *objPath, temp_);
  create_obj_folder (dir);

  snprintf (cmd, MAX_STRLEN, "g++ -c %s -o %s/%s.o\n", file, *objPath, file);

  if (get_popen (&fp, cmd, NULL) == -1)
    {
      return -1;
    }

  printf ("%s", cmd);
  if (close_popen (&fp) == -1)
    {
      char error[1024];
      while (fgets (error, 1024, fp) != NULL)
        {
          printf ("%s", error);
        }
      printf ("Error (in likely compiler)! Cannot continue!\n");
      return -1;
    }

  return 0;
}

int
link_executable (char **objPath, char **executable_name)
{
  FILE *fp;
  char cmd[MAX_STRLEN];

  snprintf (cmd, MAX_STRLEN, "g++ %s/*.o -o %s", *objPath, *executable_name);

  if (get_popen (&fp, cmd, NULL) == -1)
    {
      printf ("Having trouble linking (internal error)!\n");
      return -1;
    }
  printf ("%s\n", cmd);
  if (close_popen (&fp) == -1)
    {
      char error[1024];
      while (fgets (error, 1024, fp) != NULL)
        {
          printf ("%s", error);
        }
      printf ("Error (in likely linker)! Cannot continue!\n");
      return -1;
    }
  return 0;
}

int
create_obj_folder (char *path)
{
  DIR *dir = opendir (path);
  printf ("%d", errno);
  if (dir)
    {
      printf ("Build directory %s exists.\n", path);
      return 0;
    }
  else if (2 == errno)
    {
      printf ("Build directory %s does not exist, creating it.\n", path);
      if (mkdir (path, 0777) == -1)
        {
          printf ("Could not create build directory: %s! I can only give you "
                  "the error code:%d ",
                  path, errno);
          return -1;
        }
      return 0;
    }
  return -1;
}
