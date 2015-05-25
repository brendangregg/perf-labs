/*
 * lab006 - CPU hot stacks.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

#define SPINS	(1000 * 1000)	/* tune as desired */

void
func_c()
{
	int i;
	for (i = 0; i < SPINS; i++) { }
}

void
func_b()
{
	func_c();
}

void
func_e()
{
	int i;
	for (i = 0; i < 5 * SPINS; i++) { }
}

void
func_a()
{
	for(;;) {
		func_b();
		func_e();
	}
}

int
main(int argc, char *argv[])
{
	func_a();
	return (0);
}
