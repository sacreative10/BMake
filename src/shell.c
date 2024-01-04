// this file contains the function required by "almost" all shell commands, in
// which we get a terminal session;
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

// Returns -1 if popen had an error, 0 otherwise.
int
get_popen (FILE **pipe, char *cmd, char *err_prompt)
{
  *pipe = popen (cmd, "r");

  if (*pipe == NULL)
    {
      if (err_prompt == NULL)
        {
          perror (err_prompt);
        }
      else
        {
          perror ("(Internal Error)");
        }
      return -1;
    }
  return 0;
}

// Returns -1 if popen had an error, 0 other wise.
int
close_popen (FILE **pipe)
{
  int err = pclose (*pipe);

  if (WEXITSTATUS (err) != 0)
    {
      printf ("The compiler returned an error! Cannot continue further!");
      return -1;
    }
  return 0;
}
