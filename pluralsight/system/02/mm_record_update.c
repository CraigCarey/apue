#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

struct record
{
	int id;
	char name[80];
};

int main(void)
{
	int fd = open("foo", O_RDWR);

	// get the size of the file by seeking to end of it
	size_t size = lseek(fd, 0, SEEK_END);

	// map in the whole file,
	// the cast to records means we view it as an array of records
	struct record *records = (struct record *) mmap(NULL,
	                                                size,
	                                                PROT_READ | PROT_WRITE,
	                                                MAP_PRIVATE,
	                                                fd,
	                                                0);

	// update record 1
	records[1].id = 99;

	// sync the mapping back out to the file (since we used private flag)
	msync(records, size, MS_SYNC);
}
