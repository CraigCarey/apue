/* Measure process times */

#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>
#include <math.h>	// -lm

int main()
{	
	// frequency used by times() - probs 100Hz
	printf("clock ticks %ldHz\n", sysconf(_SC_CLK_TCK));

	// frequency used by clock() - probs 1mHz
	printf("CLOCKS_PER_SEC %ldHz\n", CLOCKS_PER_SEC);

	int fd = open("/dev/null", O_RDWR);

	for (long i = 0; i < 10000000; i++)
	{
		write(fd, &i, sizeof(i));
	}

	close(fd);

	double x;
	for (int i = 0; i < 100000000; i++)
	{
		x = sqrt((double)i);
	}

	struct tms tmsbuf;
	times(&tmsbuf);

	printf("utime = %ld\n", tmsbuf.tms_utime);
	printf("stime = %ld\n", tmsbuf.tms_stime);
	printf("cutime = %ld\n", tmsbuf.tms_cutime);
	printf("cstime = %ld\n", tmsbuf.tms_cstime);

	printf("clock = %ld\n", clock());
}
