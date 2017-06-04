#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

void privatise(char *f)
{
	// Take off all group and other perms from file f
	struct stat b;
	printf("debug: privatising %s\n", f);
	
	if (stat(f, &b) < 0)
		return;
	
	chmod(f, b.st_mode & 0700);
}

void main(int argc, char *argv[])
{

	struct stat sb;
	if (stat(argv[1], &sb) < 0)
	{
		perror("stat");
		exit(1);
	}

	// Is it a directory?
	if (S_ISDIR(sb.st_mode))
	{
		// Yes, traverse the directory and privatise all files
		chdir(argv[1]);
		DIR *d = opendir(".");
		struct dirent *info;
		while ((info = readdir(d)) != NULL)
			privatise(info->d_name);
	}
	else
	{
		// It's not a directory, privatise it
		privatise(argv[1]);
	}
}
