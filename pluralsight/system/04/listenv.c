/* List the Environment */

#include <stdio.h>

extern char **environ;

void main(int argc, char *argv[])
{
  char **p;

  for (p=environ; *p != NULL; p++)
    printf("%s\n", *p);
}
