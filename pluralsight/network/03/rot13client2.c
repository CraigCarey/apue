#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 500

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Obtain address(es) matching host/port/etc.
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6 
	hints.ai_socktype = SOCK_STREAM; // Stream socket (TCP) 
	hints.ai_flags = 0;
	hints.ai_protocol = 0;           // Any protocol 

	struct addrinfo *addresses;
	int s = getaddrinfo(argv[1], argv[2], &hints, &addresses);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	   Try each address until we successfully connect(2).
	   If socket(2) (or connect(2)) fails, we (close the socket
	   and) try the next address. */

	int sock_fd;
	struct addrinfo *address;
	for (address = addresses; address != NULL; address = address->ai_next)
	{
		sock_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
		if (sock_fd == -1)
			continue;

		if (connect(sock_fd, address->ai_addr, address->ai_addrlen) != -1)
			break; // Success

		close(sock_fd);
	}

	if (address == NULL)
	{
		// No address succeeded 
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(addresses);  // No longer needed

	/* Send each remaining command-line argument separately
	   to the server, then read and display the response. */

	for (int j = 3; j < argc; j++)
	{
		size_t len = strlen(argv[j]) + 1; // +1 for terminating null byte 

		if (len + 1 > BUF_SIZE)
		{
			fprintf(stderr,	"Ignoring long message in argument %d\n", j);
			continue;
		}

		if (write(sock_fd, argv[j], len) != len)
		{
			fprintf(stderr, "partial/failed write\n");
			exit(EXIT_FAILURE);
		}

		char buf[BUF_SIZE];
		ssize_t nread = read(sock_fd, buf, BUF_SIZE);
		if (nread == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		printf("Received %ld bytes: %s\n", (long) nread, buf);
	}

	exit(EXIT_SUCCESS);
}

