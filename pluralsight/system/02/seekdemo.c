#include <unistd.h>
#include <fcntl.h>

struct record
{
	int id;
	char name[80];
};

int main(void)
{
	int size = sizeof(struct record);
	struct record info;

	int fd = open("datafile", O_RDWR); /* Open for read/write */

	lseek(fd, size, SEEK_SET);  /* Skip one record */
	read(fd, &info, size);      /* Read second record */

	info.id = 99;               /* Modify record */
	lseek(fd, -size, SEEK_CUR); /* Backspace */
	write(fd, &info, size);     /* Write modified record */

	close(fd);
}
