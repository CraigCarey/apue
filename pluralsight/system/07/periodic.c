#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

char *p;
char buffer[10000];

void handler(void)
{
	// printf("Saving buffer...\n");
	int fd = open("buffer.save", O_RDWR|O_CREAT|O_TRUNC, 0644);
	write(fd, buffer, p-buffer);
	close(fd);
	alarm(10);
}

int main(void)
{
	// Establish SIGALRM handler
	struct sigaction action;
	action.sa_handler = (void *)handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &action, NULL);
	alarm(10);

	// Accumulate text from stdin into buffer
	int count;
	p = buffer;
	while((count = read(0, p, 200)))
		p += count;
}
