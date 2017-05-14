/* Broadcast peer-to-peer service using sockets
   Solution 2. Chris Brown 30 August 1994
   Revised 17 Sept. 1995 for Solaris 2.4 Platform
   Revised 31 July  1997 for Linux Platform

   update2.c	This solution steps the x,y values up and down in
		response to the cursor keys, and uses the x,y
		values to determine the position on the screen at
		which the text string is displayed.
*/

#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#define UPDATE_PORT	2066

/* Define the broadcast packet format */
typedef struct packet {
    char text[64];
    int  x;
    int  y;
} Packet;

/* Function prototypes */
void display_update(Packet p);

int main(int argc, char *argv[])
{
    int    sock;			/* Socket descriptor  */
    struct sockaddr_in server;		/* Broadcast address  */
    struct sockaddr_in client;
    int    client_len, yes = 1;
    Packet pkt;

    /* Initialise the curses package */
    initscr();
    cbreak();	/* Disable input buffering */
    noecho();	/* Disable echoing */

    /* Create a datagram socket and enable broadcasting*/
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof yes);

    /* Bind our well-known port number */
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port        = htons(UPDATE_PORT);
    if (bind(sock, (struct sockaddr *)&server, sizeof server) < 0) {
	printw("server: bind failed\n"); refresh(); exit(1);
    }

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = 0xffffffff;
    server.sin_port        = htons(UPDATE_PORT);

    /* Create an additional process.  The parent acts as the client,
       periodically broadcasting updates to anyone who happens to be
       listening  on  port 2066.  The  child  acts  as  the  server,
       receiving the broadcasts and displaying the data.
    */
    if (fork()) {	/* PARENT (client) here */
	if (argc>1) strcpy(pkt.text, argv[1]);
	else gethostname(pkt.text, 64);
	pkt.x = 40; pkt.y = 12;
	while (1) {
	    /* Wait for a cursor key, update x or y accordingly */
	    switch(getch()) {
	      case 65:	pkt.y--;	/* Up arrow */
			    break;
	      case 66:	pkt.y++;	/* Down arrow */
			    break;
	      case 67:	pkt.x++;	/* Right arrow */
			    break;
	      case 68:	pkt.x--;	/* Left arrow */
			    break;
	      default:	continue;
	    }
            /* Ensure co-ords have not gone out of bounds */
            if (pkt.y < 0) pkt.y  = 0;
	    if (pkt.x < 0) pkt.x  = 0;
	    if (pkt.y > 23) pkt.y = 23;
	    if (pkt.x > 75) pkt.x = 75;

	    /* Broadcast update packet to servers */
	    sendto(sock, (char *)&pkt, sizeof pkt, 0,
                   (struct sockaddr *)&server, sizeof server);
	}
    }	/* End of parent (client) code */

/* ------------------------------------------------- */

    else {	/* CHILD (server) here */
	/* Enter our service loop, receiving packets
	   and displaying them  in some appropriate way.
	*/
	while (1) {
	    /* Receive an update packet */
	    client_len = sizeof client;
	    recvfrom(sock, (char *)&pkt, sizeof pkt, 0,
                     (struct sockaddr *)&client, &client_len);

	    /* Display the packet's contents */
	    display_update(pkt);
	}
    }	/* End of child (server) code */
}

/* This version displays p.text at co-ords p.x, p.y on the screen.
   It  maintains a table  (indexed  by the text name)  of previous
   positions so that the old text can be erased
*/
void display_update(Packet p)
{
#define TSIZE	50

   static int entries = 0;
   int i, j, found;
   static struct stuff {
      char name[64];
      int  x;
      int  y;
   } table[TSIZE];

   /* Search the  table for an entry with a matching  text string.  If
      found,  the corresponding x, y values in the table  show the co-
      ordinates at which the string was previously displayed. We first
      move to this  position and erase the old string.  If no matching
      entry is found and the table is not full, a new entry is created.
   */

   for (i=0, found=0; i<entries; i++) {
      if (strcmp(p.text, table[i].name) == 0) {
         found = 1;             /* Found a matching entry */
         break;
      }
   }
   if (found) {
       /* Replace the previous instance of the string with spaces */
       move(table[i].y, table[i].x);
       for (j=0; j<strlen(p.text); j++)
           addch(' ');
       refresh();
       table[i].x = p.x;
       table[i].y = p.y;
   }
   else {
      if (entries == TSIZE)     /* Table is full */
         return;
      strcpy(table[entries].name, p.text);
      table[entries].x = p.x;
      table[entries].y = p.y;
      entries++;            /* Create new table entry */
   }

   move(p.y, p.x);
   printw(p.text); refresh();
}
