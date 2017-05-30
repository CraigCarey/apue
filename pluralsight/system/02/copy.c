/* Trivial file copy program using low-level unbuffered I/O */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// buffer size is a multiple of the block size for efficiency
#define BSIZE 16384

int main(void)
{
	int fin;

	if ((fin = open("foo", O_RDONLY)) < 0)
	{
		perror("foo");
		exit(1);
	}

	int fout;
	
	if ((fout = open("bar", O_WRONLY | O_CREAT, 0644)) < 0)
	{
		perror("bar");
		exit(2);
	}
	
	char buf[BSIZE];
	int count;

	// perform: read BSIZE bytes from fin into buf
	// assign:  bytes read to count
	// test:    repeat while > 0 bytes read
	while ((count = read(fin, buf, BSIZE)) > 0)
		write(fout, buf, count);

	close(fin);
	close(fout);
}

