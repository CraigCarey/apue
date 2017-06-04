#include <stdio.h>
#include <stdlib.h>

void main(void)
{
	int Mb = 0;

	while (malloc(1 << 20))
	{
		++Mb;
		printf("Allocated %d Mb\n", Mb);
	}

	printf("Allocated %d Mb total\n", Mb);
}