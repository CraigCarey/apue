// Equivalent to "ls | sort -r"
#include <unistd.h>

int main(void)
{
	int p[2];

	// Create the pipe
	pipe(p);

	if (fork() == 0)
	{
		// Child: connect stdout to pipe
		// (it knows it's not connected to a terminal, so formats output differently)
		dup2(p[1], 1);

		// close the downstream end (important )
		close(p[0]);
		execlp("ls", "ls", (char *)0);
	}

	// Parent: connect stdin to pipe
	dup2(p[0], 0);
	close(p[1]);
	execlp("sort", "sort", "-r", (char *)0);
}
