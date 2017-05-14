/* Demonstration of using SIGALRM to force a timeout */

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <errno.h>

void timeout_handler(int unused)
{
  /* Nothing to do */
}

int t_getnum(int timeout)
{
  int n;
  char line[100];
  struct sigaction action;

  action.sa_handler = timeout_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0; /* Important! */
  sigaction(SIGALRM, &action, NULL);

  alarm(timeout);
  n = read(0, line, 100);
  alarm(0);  /* Cancel alarm */
  if (n == -1 && errno == EINTR) return -1;
  n = atoi(line);
  return n;
}

void main()
{
  int num;

  while(1) {
    printf("enter a number: "); fflush(stdout);
    if ((num = t_getnum(5)) == -1)
      printf("timed out!\n");
    else
      printf("You entered %d\n", num);
  }
}
