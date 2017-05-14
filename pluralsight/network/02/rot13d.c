// gcc -std=c99 -Wall rot13d.c -o rot13d
// ./rot13d
// lsof -i
//   rot13d  2756 craig    3u  IPv4  25677      0t0  TCP *:1067 (LISTEN)
// telnet localhost 1067

#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#define SERVER_PORT 1067

void rot13(unsigned char *s, int n)
{
	unsigned char *p;
	for (p=s; p < s + n; p++)
	{
		if (islower(*p))
		{
			*p += 13;
			if (*p > 'z') *p -= 26;
		}
	}
}

void rot13_service(int in, int out)
{
	unsigned char buf[1024];
	int count;
	while ((count = read(in, buf, 1024)) > 0)
	{
		rot13(buf, count);
		write(out, buf, count);
	}
}

int main(void)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(SERVER_PORT);
	
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	bind(server_socket, (struct sockaddr *)&server, sizeof(server));
	listen(server_socket, 5);

	struct sockaddr_in client;
	unsigned client_len = sizeof(client);
	
	printf("listening ...\n");

	while (1)
	{
		int conn_descriptor = accept(server_socket, (struct sockaddr *)&client, &client_len);
		printf("got connection\n");
		rot13_service(conn_descriptor, conn_descriptor);
		close(conn_descriptor);
		printf("closed connection\n");
	}
}

