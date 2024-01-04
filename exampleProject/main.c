
#include "add.h"
#include "sub.h"
#include <stdio.h>

int
main ()
{
  int x = 5;
  int y = 10;
  printf ("Answer is: %d\n", add (x, y));

  printf ("The second answer is: %d\n", sub (x, y));

  return 0;
}
