// Client for rot13 server
// gcc -std=c99 -Wall rot13client1.c -o rot13client1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define BSIZE 1024
#define ROT13PORT 1067
#define h_addr h_addr_list[0] // for backward compatibility

int main(int argc, char *argv[])
{
	// Get server name from command line. If none, use "localhost"
	char * server_name = (argc>1) ? argv[1] : "localhost";

	// Create the socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("creating stream socket");
		exit(1);
	}

	// Look up the host's IP address
	struct hostent *host_info = gethostbyname(server_name);
	if (host_info == NULL)
	{
		fprintf(stderr, "%s: unknown host: %s\n", argv[0], server_name);
		exit(2);
	}

	// Set up the server's socket address & port
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	memcpy((char *)&server.sin_addr, host_info->h_addr, host_info->h_length);
	server.sin_port = htons(ROT13PORT);

	// Connect to the server
	if (connect(sock,(struct sockaddr *)&server,sizeof server) < 0)
	{
		perror("connecting to server");
		exit(4);
	}

	// Now we are connected to the server. Send the user name, then
	// collect whatever the server sends back and copy it to stdout
	printf("connected to server %s\n", server_name);

	int count;
	char buf[BSIZE];
	while((count = read(0, buf, BSIZE)) > 0)
	{
		write(sock, buf, count);
		read(sock, buf, count);
		write(1, buf, count);
	}
}
