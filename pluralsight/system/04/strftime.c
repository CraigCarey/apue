// Simple demo of strftime
#include <stdio.h>
#include <time.h>		// time()
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "");

	// 32 bit int, seconds since the epoch (1/1/1970 UTC )
	time_t t = time(NULL);

	// broken-down time
	// struct tm *	bdtime = gmtime(&t);	// GMT
	struct tm *	bdtime = localtime(&t);		// local time

	char buf[1000];
	strftime(buf, 1000, "It is %H:%M on %A %d %B %Y", bdtime);
	puts(buf);

	return 0;
}

