#include <stdio.h>
#include <signal.h>
#include <string.h>

int main(void)
{
	for (int i = 1; i < 16; i++)
		printf("Signal %2d: %s\n", i, strsignal(i));
}
