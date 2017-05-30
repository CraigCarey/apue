#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	// open 'foo' for writing only, creating if doesn't exist
	// with file permissions -rw-r--r--
	int fd = open("foo", O_WRONLY | O_CREAT, 0644);
	write(fd, "hello world", 11);
	close(fd);
}
