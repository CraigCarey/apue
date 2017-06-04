#include	<sys/wait.h>
#include	<errno.h>
#include	<unistd.h>

int system(const char *cmdstring)	/* version without signal handling */
{
	pid_t pid;
	int status;

	if (cmdstring == NULL)
	{
		/* always a command processor with UNIX */
		return(1);
	}

	if ((pid = fork()) < 0)
	{
		status = -1;	/* probably out of processes */
	}
	else if (pid == 0)
	{	
		/* child */
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		
		/* execl error */
		_exit(127);
	}
	else
	{	
		/* parent */
		while (waitpid(pid, &status, 0) < 0)
		{
			if (errno != EINTR)
			{
				/* error other than EINTR from waitpid() */
				status = -1;
				break;
			}
		}
	}

	return(status);
}
