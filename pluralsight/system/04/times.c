#include <stdio.h>
#include <time.h>		// time(), ctime(), gmtime(), localtime(), asctime()
#include <sys/time.h>	// timeval, gettimeofday()
#include <sys/times.h>	// times()
#include <unistd.h>		// sysconf()

// time_t is seconds since the epoch, expressed as an unsigned long
// used by ctime, gmtime and localtime
// ctime returns formatted human-readable string
// gmtime and localtime convert a time_t to a tm struct

// timeval is a struct containing seconds and microseconds since the epoch
//	struct timeval {
//		time_t      tv_sec;
//		suseconds_t tv_usec;
//	};
// filled by gettimeofday(), useful for timing operations

// broken down time is stored in the structure tm
// 	struct tm {
//		int tm_sec;		/* Seconds (0-60) */
//		int tm_min;		/* Minutes (0-59) */
//		int tm_hour;	/* Hours (0-23) */
//		int tm_mday;	/* Day of the month (1-31) */
//		int tm_mon;		/* Month (0-11) */
//		int tm_year;	/* Year - 1900 */
//		int tm_wday;	/* Day of the week (0-6, Sunday = 0) */
//		int tm_yday;	/* Day in the year (0-365, 1 Jan = 0) */
//		int tm_isdst;	/* Daylight saving time */
//	};
// tms are formatted into human-readable strings by
// strftime (customisable)
// asctime (standard format, same as ctime)

// times() stores the current process times in the struct tms
//	struct tms {
//		clock_t tms_utime;  /* user time */
//		clock_t tms_stime;  /* system time */
//		clock_t tms_cutime; /* user time of children */
//		clock_t tms_cstime; /* system time of children */
//	};


int main(void)
{
	printf("\nwall-clock time:\n\n");

	// values obtained from kernel
	time_t t1 = time(NULL);
	struct timeval t2;
	gettimeofday(&t2, NULL);

	// take a time_t
	printf("ctime(time_t t1):\t(%lu) %s", t1, ctime(&t1));
	struct tm *t4 = gmtime(&t1);
	struct tm *t5 = localtime(&t1);

	// takes a timeval
	printf("gettimeofday(timeval):\t%ld(s) %ld(us)\n", t2.tv_sec, t2.tv_usec);

	// take a tm
	char t7[1000];
	strftime(t7, 1000, "%H:%M on %A %d %B %Y", t4);
	printf("strftime(struct tm t4):\t%s\n",t7);
	printf("asctime(struct tm t5):\t%s", asctime(t5));

	printf("\nsystem time:\n\n");

	// frequency used by times() - probs 100Hz
	printf("clock ticks %ldHz\n", sysconf(_SC_CLK_TCK));

	// frequency used by clock() - probs 1mHz
	printf("CLOCKS_PER_SEC %ldHz\n", CLOCKS_PER_SEC);

	struct tms tmsbuf;
	times(&tmsbuf);

	printf("utime = %ld\n", tmsbuf.tms_utime);
	printf("stime = %ld\n", tmsbuf.tms_stime);
	printf("cutime = %ld\n", tmsbuf.tms_cutime);
	printf("cstime = %ld\n", tmsbuf.tms_cstime);

	printf("clock = %ld\n", clock());

	puts("");
}
