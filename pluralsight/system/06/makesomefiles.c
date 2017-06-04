#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
	// clear umask so it has no effect
	umask(0);
	creat("f1", 0755);              // rwxr-xr-x

	// mask rw for 'other'
	umask(007);
	creat("f2", 0755);              // rwxr-x---

	// create with no permissions
	creat("f3", 0);

	// add rw permissions for user
	chmod("f3", S_IRUSR | S_IWUSR); // rw-------

	system("ls -l f?");
}
