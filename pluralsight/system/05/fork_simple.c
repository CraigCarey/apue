#include <stdio.h>
#include <unistd.h>

int fx(void)
{
	static int x = 13;
	return x++;
}

int main(void)
{
	printf("fx:\t%p\n", fx);

	if (fork())
	{
		int i = 100;
		printf("PARENT - i = %d, &i = %p, fx = %p, x = %d\n", i, &i, fx, fx());
	}
	else
	{
		int i = 213;
		printf("CHILD - i = %d,  &i = %p, fx = %p, x = %d\n", i, &i, fx, fx());
	}
	
	printf("PARENT2 - x = %d\n", fx());

}

