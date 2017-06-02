// Monitor specified files for change, using inotify
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>

// A buffer big enough to read 100 events in one go
#define BUFSIZE (100 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(void)
{
	// Open the config file
	FILE *fconfig;
	if ((fconfig = fopen("monitor.conf", "r"))  == NULL)
	{
		printf("unable to open the config file; giving up!\n");
		exit(1);
	}

	// Not checked for error
	int notifyfd = inotify_init();

	// Holds the names of the watched files
	// indexed by the watch descriptor
	char watchednames[100][NAME_MAX+1];

	// Read all watched file names from config file
	char watchname[1000];
	while (fgets(watchname, 1000, fconfig) != NULL)
	{
		// Get rid of the newline
		watchname[strlen(watchname)-1] = '\0';

		struct stat sb;
		if (stat(watchname, &sb) < 0)
		{
			printf("Cannot stat %s, ignored\n", watchname);
			continue;
		}

		if (S_ISREG(sb.st_mode))
		{
			int watchfd;
			// Regular file, so add to watch list
			if ((watchfd = inotify_add_watch(notifyfd, watchname, IN_MODIFY | IN_DELETE_SELF)) < 0)
			{
				printf("error adding watch for %s\n", watchname);
			}
			else
			{
				printf("added %s to watch list on descriptor %d\n", watchname, watchfd);
				// Record the file we're watching on this watch descriptor
				// There should be a check on overflow of the watchednames array
				strcpy(watchednames[watchfd], watchname);
			} 
		}
		else
		{ 
			// Probably a directory
			printf("%s is not a regular file, ignored\n", watchname);
		}
	}

	// All our watches are in place, so just read and report events
	FILE *fout = fopen("monitor.out", "a");

	while(1)
	{
		char eventbuf[BUFSIZE];

		// This read will block until an event is delivered
		int n = read(notifyfd, eventbuf, BUFSIZE);

		// Loop over all events and report them. This is a little tricky
		// because the event records are not of fixed length
		for (char *p = eventbuf; p < eventbuf + n;)
		{
			struct inotify_event *event = (struct inotify_event *) p;

			// increment pointer by size of event
			p += sizeof(struct inotify_event) + event->len;
			
			// Display the event 
			if (event->mask & IN_MODIFY) fprintf(fout, "%s was modified\n", watchednames[event->wd]);
			if (event->mask & IN_DELETE_SELF) fprintf(fout, "%s was deleted\n", watchednames[event->wd]);
			fflush(fout);
		}
	}
}

