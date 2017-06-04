#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
	// Print old umask and set new one
	printf("previous umask 0%o\n", umask(0));
	open ("f1", O_RDWR | O_CREAT, 0644);
	fopen("f2", "w");

	umask(027);
	open ("f3", O_RDWR | O_CREAT, 0777);
	fopen("f4", "w");

	system("ls -l f?");
}
