#include <stdio.h>


extern char **environ;

/* Get all values using global environ variable. Probably prefer
   this because it can be handled at a lower level than main */
int main(void)
{
	for (; *environ; environ++)
	{
		printf("%s\n", *environ);
	}

	return 0;
}


/*
	get all env variables using values passed in from start-up routine
	int main(int argc, char **argv, char** envp)
	{
		for (; *envp; envp++)
		{
			printf("%s\n", *envp);
		}

		return 0;
	}
*/