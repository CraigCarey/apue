// Build histogram of modification hour of files
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

// Hour-by-hour histogram of modification time
int modtimehist[24];
int rflag=0;
int aflag=0;

void processfile(char *name)
{
	struct stat sb;

	// Broken down time
	struct tm* bdtime;

	printf("processing file %s\n", name); 
	
	if (stat(name, &sb) < 0)
	{
		perror(name);
		exit(2);
	}

	bdtime = localtime(&sb.st_mtime);
	modtimehist[bdtime->tm_hour]++;
}

void processdir(char *dirname)
{

	printf("processing directory %s\n", dirname);
	DIR *d = opendir(dirname);
	
	if (d == NULL)
	{
		perror(dirname);
		exit(1);
	}

	struct dirent *info;
	char fullfilename[PATH_MAX];
	struct stat sb;
	
	while ((info = readdir(d)) != NULL)
	{
		if (info->d_name[0] == '.' && !aflag) continue;

		// Build absolute name of file
		strcpy(fullfilename, dirname);
		strcat(fullfilename, "/");
		strcat(fullfilename, info->d_name);
		
		// Recurse if rflag set, but not on "." or ".."
		stat(fullfilename, &sb);
		if (strcmp(info->d_name, ".")
		     && strcmp(info->d_name, "..")
		     && rflag
		     && S_ISDIR(sb.st_mode))
		{
			// Recurse
			processdir(fullfilename);
		}
		else
		{
			processfile(fullfilename);
		}
	}
	closedir(d);
}

int main(int argc, char * argv[])
{
	char dirname[PATH_MAX];

	// Zero out the histogram
	for (int i = 0; i < 24; i++) modtimehist[i] = 0;

	// Suppress getopt's own error messages
	opterr = 0;

	int c;
	while ( (c = getopt(argc, argv, "ar")) != EOF)
	{
		switch (c)
		{
			case 'a':
				aflag = 1;
				break;
			case 'r':
				rflag = 1;
				break;
			case '?':
				fprintf(stderr, "invalid option: -%c\n", optopt);
		}
	}

	// Adjust to move past the options
	argv += optind;
	argc -= optind;

	if (argc != 1)
	{
		fprintf(stderr, "usage: modtimehist [-a] [-r] dirname\n");
		exit(1);
	}

	// If not an absolute path, make it so
	if (argv[0][0] == '/')
	{
		strncpy(dirname, argv[0], PATH_MAX);
	}	
	else
	{
		getcwd(dirname, PATH_MAX);
		strcat(dirname, "/");
		strcat(dirname, argv[0]);
	}

	processdir(dirname);

	// Display the histogram
	for (int i = 0; i < 24; i++)
		printf("hour %2d: count = %6d\n", i, modtimehist[i]);
}
