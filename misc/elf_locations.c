// ll a.out; size a.out
// nm a.out
// readelf -Ws a.out

char pear[40];
static double peach;
int mango = 13;
static long melon = 2001;

char jack[] = "All work and no play makes Jack a dull boy";

void fx()
{
	int laii[1000] = { 13 };
}

main()
{
	int i = 3, j, *ip;
	ip = malloc(sizeof(i));
	pear[5] = i;
	peach = 2.0 * mango;
	fx();
}