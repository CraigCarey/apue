#include <time.h>
#include <stdio.h>
#include <locale.h>

int main()
{
  time_t t;
  struct tm * lt;
  char buf[1000];

  if (setlocale(LC_ALL, "") == NULL) {
    printf("setlocale failed\n");
  }
  t = time(NULL);
  printf("ctime: %s", ctime(&t));
  lt = localtime(&t);
  strftime(buf, 1000, "%R %A %e %B", lt);
  printf("strftime: %s\n", buf);
}

