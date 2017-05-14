/* Simple demonstration of changing file permissions */

#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

void privatise(char *f)
// Take of all group and other perms from file f
{
  struct stat b;
  printf("debug: privatising %s\n", f);
  if (stat(f, &b) < 0)
    return;
  chmod(f, b.st_mode & 0700);
}

void main(int argc, char *argv[])
{
  struct stat buf;
  DIR *d;
  struct dirent *info;

  // Is it a directory?
  if (stat(argv[1], &buf) < 0) {
    perror("stat");
    exit(1);
  }
 
  if (S_ISDIR(buf.st_mode))
  {
    // Yes, traverse the directory and privatise all files
    chdir(argv[1]);
    d = opendir(".");
    while ((info = readdir(d)) != NULL)
      privatise(info->d_name);
  }
  else /* It's not a directory */
  {
    privatise(argv[1]);
  }
}
