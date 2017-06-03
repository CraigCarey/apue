#include <stdio.h>
#include <unistd.h>

/*
The key point is that the parent and child output will be interleaved in
a non-deterministic way. If you run the program several times, this
behaviour shows up clearly. Occasionally you may see child output appearing
AFTER the prompt. This is expected behaviour.
*/

int main(void)
{
	int i;

	if (fork())
	{
		for (i=0; i<100000; i++)
			printf("**     PARENT %d\n", i);
	}
	else
	{
		for (i=0; i<100000; i++)
			printf("  **   CHILD  %d\n", i);
	}
}

