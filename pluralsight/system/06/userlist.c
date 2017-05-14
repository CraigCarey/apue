/* Demonstration of password file enumeration */
/* Lists those users with uid >= 1000 */

#include <stdio.h>
#include <pwd.h>

void main(int argc, char *argv[])
{
  struct passwd *u;

  while ((u = getpwent()) != NULL) {
    if (u->pw_uid >= 1000)
      printf("%s\n", u->pw_name);
  }
}
