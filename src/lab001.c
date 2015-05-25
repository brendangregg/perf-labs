/*
 * lab001 - CPU hot stack.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

void
func_c()
{
	for(;;){}
}

void
func_b()
{
	func_c();
}

void
func_a()
{
	func_b();
}

int
main(int argc, char *argv[])
{
	func_a();
	return (0);
}
