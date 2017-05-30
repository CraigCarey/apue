#include <unistd.h>

int main(void)
{
	// write 12 chars of string to stdout (1)
	write(1, "Hello world\n", 12);
}
