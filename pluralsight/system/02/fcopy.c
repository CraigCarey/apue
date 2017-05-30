#include <stdio.h>

#define BSIZE 16384

int main(void)
{
	FILE *fin = fopen("foo", "r");
	FILE *fout = fopen("bar", "w");

	int count;
	char buf[BSIZE];

	// read 1 item of BSIZE size from fin into buf
	while ((count = fread(buf, 1, BSIZE, fin)) > 0)
	{
		printf("transferring %d bytes\n", count);
		// write 1 item of count size from buf to fout
		fwrite(buf, 1, count, fout);
	}

	fclose(fin);
	fclose(fout);
}
