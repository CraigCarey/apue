#include <stdio.h>
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

	FILE *fd = fopen("bufio.out", "w");
	
	for (int i = 0; i < count; i++)
	{
		fwrite(buffer, size, 1, fd);
	}

	fclose(fd);
}
