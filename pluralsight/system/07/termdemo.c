#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	if (fork())
	{
		// Parent
		int status;
		wait (&status);
		if (WIFEXITED(status))
			printf("Child exited normally with exit status %d\n", WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			printf("Child exited on signal %d: %s\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
	}
	else
	{
		// Child
		printf("Child PID = %d\n", getpid());
		
		// cast zero to an int pointer and try to write to it
		// to trigger a segfault
		// *(int *)0 = 99;

		// trigger a floating point exception
		// int a = 1, b = 0, c = a/b;

		// child will block on this call
		pause();

		sleep(3);
		exit(5);
	}
}
