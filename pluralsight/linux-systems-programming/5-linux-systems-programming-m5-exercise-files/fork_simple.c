/* File fork_demo2.c */
#include <stdio.h>

void main()
{
    if (fork())
      printf("PARENT\n");
    else
      printf("CHILD\n");
}

