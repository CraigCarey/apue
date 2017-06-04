#include <stdio.h>
#include <stdlib.h>

int globalUninit;                    // bss
int globalInit = 13;                 // data
static int globalStaticUninit;       // bss
static int globalStaticInit = 45;    // data
int globalArrayUninit[100];          // bss
int globalArrayInit[100] = { 35 };   // data

void fx(void) // text
{
	int localUninit;                 // stack
	int localInit = 13;				 // stack
	static int localStaticUninit;    // bss
	static int localStaticInit = 99; // data

	printf("localUninit: %p\t(stack)\n", &localUninit);
	printf("localInit: %p\t(stack)\n", &localInit);
	printf("localStaticUninit: %p\t(bss)\n", &localStaticUninit);
	printf("localStaticInit: %p\t(data)\n", &localStaticInit);
}

int main(void)                       // text
{
	int i;                           // stack
	int *x = malloc(sizeof(int));    // heap
	puts("");
	printf("The stack top is near: %p\n", &i);
	printf("The heap top is near: %p\n", x);
	printf("The data section is near: %p\n", & globalInit);
	printf("The text section is near: %p\n", &fx);
	printf("The BSS section is near: %p\n", &globalUninit);
	puts("");
	printf("globalUninit: %p\t\t(bss)\n", &globalUninit);
	printf("globalInit: %p\t\t(data)\n", &globalInit);
	printf("globalStaticUninit: %p\t(bss)\n", &globalStaticUninit);
	printf("globalStaticInit: %p\t(data)\n", &globalStaticInit);
	printf("globalArrayUninit: %p\t(bss)\n", &globalArrayUninit);
	printf("globalArrayInit: %p\t(data)\n", &globalArrayInit);
	printf("fx: %p\t\t\t(text)\n", &fx);
	puts("");
	fx();
	puts("");
	return 0;
}