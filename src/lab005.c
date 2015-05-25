/*
 * lab005 - sync disk writes to a file.
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *datafile = "lab005.data";

#define BUFSIZE		(8 * 1024)
#define FILESIZE	(10 * 1024 * 1024)

void
write_log(int fd)
{
	char buf[BUFSIZE];
	int i;

	for (;;) {
		for (i = 0; i < FILESIZE / BUFSIZE; i++) {
			if (write(fd, buf, BUFSIZE) < 0) {
				printf("ERROR: write error.\n");
				exit(2);
			}
		}

		if (lseek(fd, 0, SEEK_SET) < 0) {
			printf("ERROR: seek() failed.\n");
			exit(3);
		}
	}
}

int
main()
{
	int fd;

	if ((fd = open(datafile, O_CREAT | O_WRONLY | O_SYNC, 0644)) < 0) {
		printf("ERROR: writing to %s\n", datafile);
		exit(1);
	}

	write_log(fd);

	return (0);
}
