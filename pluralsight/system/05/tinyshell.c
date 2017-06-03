#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	char line[100];

	while (printf("> "), gets(line) != NULL)
	{
		if (fork() == 0)
		{
			// The first argument to execlp is the name of the executable,
			// which will be looked up on the search path (defined by PATH)
			// The remaining arguments are the command line args that will
			// be passed to the program, with a terminating NULL			
			execlp(line, line, (char *)0);

			// Don't come here unless execlp fails
			printf("%s: not found\n", line);
			exit(1);
		}
		else
		{
			wait(0);
		}
		
		// Now loop back and prompt again
	}
}

