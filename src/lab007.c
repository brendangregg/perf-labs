/*
 * lab007 - asleep in function call.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

#include <unistd.h>

#define SPINS	(10 * 1000 * 1000)	/* tune to ~1% CPU */

void
func_l()
{
	int i, j;

	for(;;) {
		usleep(1000 * 1000);
		for (i = 0, j = 0; i < SPINS; i++) { j++; }
	}
}

void
func_k()
{
	func_l();
}

void
func_j()
{
	func_k();
}

int
main(int argc, char *argv[])
{
	func_j();
	return (0);
}
