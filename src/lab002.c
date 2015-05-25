/*
 * lab002 - waiting on accept().
 *
 * 21-May-2015	Brendan Gregg	Created this.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFSIZE	256
#define PORT	12340

void
connection_handler(int connection_fd)
{
	int nbytes;
	char buffer[BUFSIZE];

	nbytes = read(connection_fd, buffer, BUFSIZE);
	buffer[nbytes] = 0;

	nbytes = sprintf(buffer, "Shhh... I'm sleeping.\n");
	write(connection_fd, buffer, nbytes);
}

void
wait_for_work(int socket_fd)
{
	int connection_fd;
	struct sockaddr_in client;
	socklen_t length;

	length = sizeof (client);

	while((connection_fd = accept(socket_fd, 
	    (struct sockaddr *) &client, &length)) > -1) {
		connection_handler(connection_fd);
		close(connection_fd);
	}

}

int
main(int argc, char *argv[])
{
	struct sockaddr_in address;
	int socket_fd, connection_fd;
	size_t address_length;
	pid_t child;
	struct hostent *server;

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("ERROR: socket() failed\n");
		exit(1);
	} 

	bzero((char *) &address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
	{
		printf("ERROR: bind() failed");
		exit(2);
	}

	if (listen(socket_fd, 5) != 0) {
		printf("ERROR: listen() failed\n");
		exit(3);
	}

	wait_for_work(socket_fd);

	close(socket_fd);
	return (0);
}
