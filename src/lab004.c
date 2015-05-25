/*
 * lab004 - short lived cksum processes.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *datafile = "lab004.data";

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
check_log()
{
	char cmd[256];
	snprintf(cmd, sizeof (cmd), "cksum %s >/dev/null 2>&1", datafile);

	system(cmd);
}

int
main()
{
	init_data();

	for (;;) {
		check_log();
	}

	return (0);
}
