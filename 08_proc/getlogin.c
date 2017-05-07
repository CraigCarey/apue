#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char * login = getlogin();

	/* Doesn't work on Mint 18?? */
	printf("login: %s\n", login);
}