#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void myhandler(int sigtype)
{
	printf("got signal %d\n", sigtype);
}

int main(void)
{
	int p[2];

	pipe(p);

	struct sigaction action;
	action.sa_handler = myhandler;
	sigemptyset(&action.sa_mask);
	// action.sa_flags = 0;			// system calls will return error
	action.sa_flags = SA_RESTART;	// system calls will resume

	sigaction(SIGINT, &action, NULL);

	char buf[1000];
	while(1)
	{
		int n = read(p[0], buf, 1000);
		printf("read returned %d, errno = %d\n", n, errno);
	}
}
