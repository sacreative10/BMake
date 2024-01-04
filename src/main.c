#include "compiler.h"
#include "project_files.h"
#include <stdio.h>
#include <string.h>
int
main (int argc, char *argv[])
{
  char *pathToProject = "src";
  char *pathToObjs = "objv";
  char *executable = "bmake";

  // firstly find how many files exist
  int n_files = get_number_of_source_files (&pathToProject);
  printf ("%d source files found!\n", n_files);
  if (n_files == -1)
    {
      return -1;
    }
  char filenames[n_files][MAX_STRLEN];

  if (get_source_files (&pathToProject, filenames) == -1)
    {
      return -1;
    }

  if (create_obj_folder (pathToObjs) == -1)
    {
      printf ("Could not create directory(s)!\n");
      return -1;
    }

  for (int i = 0; i <= n_files - 1; i++)
    {
      filenames[i][strlen (filenames[i]) - 1] = 0;
      if (compile_file (filenames[i], &pathToObjs) == -1)
        {
          printf ("Compilation failed!\n");
          return -1;
        }
    }

  if (link_executable (&pathToObjs, &executable) == -1)
    {
      printf ("Linking Failed\n");
      return -1;
    }

  printf ("Compilation and Linking successful\n");
  return 0;
}
