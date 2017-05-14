#include <stdio.h>
#include <signal.h>
#include <string.h>

main()
{
  int i = 0;

  for (i = 1; i < 16; i++)
    printf("Signal %2d: %s\n", i, strsignal(i));
}
