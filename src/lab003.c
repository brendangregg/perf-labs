/*
 * lab003 - 0 byte successful reads.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *datafile = "lab003.data";

#define BUFSIZE		(8 * 1024)
#define FILESIZE	(10 * 1024 * 1024)

void
init_data()
{
	int fd;
	long long i;
	char buf[BUFSIZE];

	if ((fd = open(datafile, O_CREAT | O_WRONLY, 0644)) < 0) {
		printf("ERROR: Can't open datafile: %s\n", datafile);
		exit(1);
	}

	for (i = 0; i < FILESIZE / BUFSIZE; i++) {
		if (write(fd, buf, BUFSIZE) < 0) {
			printf("ERROR: write error.\n");
			exit(2);
		}
	}

	close(fd);
}

void
load_data()
{
	int fd;
	char buf[1];

	if ((fd = open(datafile, O_RDONLY)) < 0) {
		printf("ERROR: Can't open database: %s\n", datafile);
		exit(2);
	}

	for (;;) { read(fd, &buf, 0); }

	(void) close(fd);
}

void
import_database()
{
	load_data();
}

int
main()
{
	init_data();

	for (;;) {
		import_database();
	}

	return (0);
}
