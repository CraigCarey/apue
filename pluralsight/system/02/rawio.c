#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage: %s blocksize blockcount\n", argv[0]);
		exit(1);
	}

	int size  = atoi(argv[1]);
	int count = atoi(argv[2]);
	char *buffer = malloc(size);

	int fd = open("rawio.out", O_WRONLY | O_CREAT | O_TRUNC, 0600);

	for (int i = 0; i < count; i++)
	{
		write(fd, buffer, size);
	}

	close(fd);
}
