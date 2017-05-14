/* Trivial program to create zombies */

#include <unistd.h>
#include <stdlib.h>

main()
{
  if (fork() == 0) exit(0);
  sleep(1000);
}

