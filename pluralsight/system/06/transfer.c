// gcc -D Debug transfer.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// Deal with the command line flags (-g only!)
	int c = 0;
	int gflag = 0;
	while ((c = getopt(argc, argv, "g")) != EOF)
	{
		switch(c)
		{
			case 'g':
				gflag = 1;
				break;
			case '?':
				fprintf(stderr, "invalid option: -%c\n", optopt);
				break;
		}
	}

	// Adjust to move past the options
	argv += optind-1;
	argc -= optind-1;

	// Sanity-check the (non-option part of the) command line
	if (argc != 4)
	{
		fprintf(stderr, "usage: transfer old_owner new_owner dir\n");
		exit(1);
	}

	// Open the directory
	DIR *dir = opendir(argv[3]);
	if (dir == NULL)
	{
		perror(argv[3]);
		exit(1);
	}

	// Look up the old and new user names in the account database,
	// and get their numeric ids.  If either doesn't exist,  print
	// an error and exit
	struct passwd *user1;
	if ((user1 = getpwnam(argv[1])) == NULL)
	{
		fprintf(stderr, "unknown user: %s\n", argv[1]);
		exit(1);
	}

	int uid1 = user1->pw_uid;

	struct passwd *user2;
	if ((user2 = getpwnam(argv[2])) == NULL)
	{
		fprintf(stderr, "unknown user: %s\n", argv[2]);
		exit(1);
	}

	int uid2 = user2->pw_uid;
	int gid2 = user2->pw_gid;

	#ifdef DEBUG
	 printf("uid1 = %d, uid2 = %d\n", uid1, uid2);
	#endif

	// Implement a policy that only the real root can give files to root
	if ((uid2 == 0) && (getuid() != 0) )
	{
		printf("only root can do that\n");
		exit(1);
	}

	// Loop round all the files in the directory
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
		// Build the full filename
		char fullname[1024];
		sprintf(fullname, "%s/%s", argv[3], entry->d_name);

		// stat the file
		struct stat info;
		if (stat(fullname, &info) < 0)
		{
			fprintf(stderr, "%s: ", fullname);
			perror("stat failed");
			continue;
		}

		// Process the file if it belongs to uid1 and is a reg file
		if ((info.st_uid == uid1) & S_ISREG(info.st_mode))
		{
			#ifdef DEBUG
			printf("changing owner of %s\n", entry->d_name);
			#endif

			if (chown(fullname, uid2, gflag ? gid2 : -1) < 0)
			{
				perror(fullname);
			}
		}
	}
	
	// Close the directory -- Unlikely to fail, not checked
	closedir(dir);

	exit(0);
}
