#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd = open("foo", O_WRONLY | O_CREAT, 0644);

	if (fd < 0)
	{
		printf("error number %d\n", errno);
		perror("foo");
		exit(1);
	}

	write(fd, "hello world", 11);
	close(fd);
}
