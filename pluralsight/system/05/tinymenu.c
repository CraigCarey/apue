#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i;

	printf("0=ps, 1=ls, 2=date 3=goof : ");
	scanf("%d", &i);

	static char *cmd[] = { "ps", "ls", "date", "goof" };
	// path, command, argument list
	execlp(cmd[i], cmd[i], NULL);

	printf("command not found\n");
}
