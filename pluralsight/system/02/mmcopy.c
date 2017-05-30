#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	// Open the source file
	int fin = open("foo", O_RDONLY);
	if (fin < 0)
	{
		perror("foo");
		exit(1);
	}

	// Get the size of the file
	// We use this to specify the size of the two mappings
	size_t size = lseek(fin, 0, SEEK_END);

	// Map in the entire source file into the in-memory buffer src
	char *src = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fin, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap");
		exit(2);
	}

	// Open the destination file
	int fout = open("bar", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fout < 0)
	{
		perror("bar");
		exit(1);
	}

	// Set the size of the output file to match the input file size
	if (ftruncate(fout, size) == -1)
	{
		perror("ftruncate");
		exit(3);
	}

	// Map the destination file into the in-memory buffer dst
	char *dst = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fout, 0);
	if (dst == MAP_FAILED)
	{
		perror("mmap");
		exit(4);
	}

	// Copy bytes between source and destination mappings
	memcpy(dst, src, size);

	// Flush changes to dest mapping back out to the file
	// Not strictly necessary here, as when the application
	// ends mappings are removed and contents flushed to file
	if (msync(dst, size, MS_SYNC) == -1)
	{
		perror("msync");
		exit(5);
	}

	exit(0);
}
