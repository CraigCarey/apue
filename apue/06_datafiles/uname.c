#include <sys/utsname.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
	struct utsname utn;

	if (uname(&utn))
	{
		perror("error\n");
		return 1;
	}

	printf("sysname:     %s\n", utn.sysname);
	printf("nodename:    %s\n", utn.nodename);
	printf("release:     %s\n", utn.release);
	printf("version:     %s\n", utn.version);
	printf("machine:     %s\n", utn.machine);
	printf("domainname:  %s\n", utn.domainname);

	/* version of the ISO POSIX-1 standard (C language binding) */
	printf("POSIX.1 Ver:           %ld\n", _POSIX_VERSION);
	/* version of the ISO POSIX-2 standard (Commands) */
	printf("POSIX.2 Ver:           %ld\n", _POSIX2_VERSION);
	/* version of the ISO POSIX-2 standard (C language binding) */
	printf("_POSIX2_C_VERSION Ver: %ld\n", _POSIX2_C_VERSION);
	/* version of the X/Open Portability Guide */
	printf("_XOPEN_VERSION Ver:    %d\n", _XOPEN_VERSION);

	char hostName[64];

	if (gethostname(&hostName[0], 64))
	{
		perror("error\n");
		return 1;
	}

	printf("hostname:     %s\n", hostName);

	return 0;
}
