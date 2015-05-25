/*
 * lab013 - out of memory by recursion. tricky.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

void
func_r()
{
	int i;
	for (i = 0; i < 100; i++) { }
	func_r();
}

int
main(int argc, char *argv[])
{
	func_r();
	return (0);
}
