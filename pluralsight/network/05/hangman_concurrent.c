/* Concurrent hangman server */

#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

extern time_t time();

char *word[] = {
#include "words"
               };

#define NUM_OF_WORDS	(sizeof(word)/sizeof(word[0]))
#define MAXLEN	80	/* Maximum size of any string in the world */
#define HANGMAN_TCP_PORT	1068

void play_hangman(int in, int out);

int main(int argc, char * argv[])
{
    int sock, msgsock, client_len;
    struct sockaddr_in server, client;

    signal(SIGCHLD, SIG_IGN);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
	perror("creating stream socket");
	exit(1);
    }

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port        = htons(HANGMAN_TCP_PORT);

    if (bind(sock, (struct sockaddr *) &server, sizeof (server)) < 0) {
	perror("binding socket");
	exit(2);
    }

    listen(sock, 5);
    fprintf(stderr, "hangman server: listening...\n");

    while (1) {
	client_len = sizeof(client);
	msgsock = accept(sock, (struct sockaddr *) &client, &client_len);
	if (msgsock < 0) {
	    perror("accepting connection");
	    exit(3);
	}
        if (fork() == 0) {
            close(sock);        /* Child -- Process Request */
	    printf("new child (pid %d) using descriptor %d\n", getpid(), msgsock);
            srand((int)time((long *)0));	/* Randomise the seed */
	    play_hangman(msgsock, msgsock);
            printf("child (pid %d) exiting\n", getpid());
            exit(0);
        }
        else
	    close(msgsock);
    }

    /* done */
    return 0;
}

/* ------------------ play_hangman() ------------------------ */
/* Plays one game of hangman,  returning when the  word has been
   guessed or all the player's "lives" have been used.  For each
   "turn"  of the game,  a line is read  from  stream "in".  The
   first character of this line is  taken as the player's guess.
   After each guess and prior to the first guess, a line is sent
   to stream "out". This consists of the word as guessed so far,
   with - to show unguessed letters,   followed by the number of
   lives remaining.
   Note that this function neither knows nor cares  whether its
   input and output streams refer to sockets, devices, or files.
*/
void play_hangman(int in, int out)
{
    char *whole_word, part_word[MAXLEN], guess[MAXLEN], outbuf[MAXLEN];
    int lives   = 12;		/* Number of lives left */
    int game_state = 'I';	/* I ==> Incomplete     */
    int i, good_guess, word_length;

    /* Pick a word at random from the list */
    whole_word = word[rand() % NUM_OF_WORDS];
    word_length = strlen(whole_word);

    /* No letters are guessed initially */
    for (i=0; i < word_length; i++)
	part_word[i] = '-';
    part_word[i] = '\0';

    sprintf(outbuf, " %s   %d\n", part_word, lives);
    write(out, outbuf, strlen(outbuf));

    while ( game_state == 'I')
      { read(in, guess, MAXLEN);	/* Get guess letter from player */
	good_guess = 0;
	for (i=0; i<word_length; i++)
	  { if (guess[0] == whole_word[i])
	      { good_guess = 1;
		part_word[i] = whole_word[i];
              }
	  }
        if (! good_guess) lives--;
	if (strcmp(whole_word, part_word) == 0)
	    game_state = 'W';		/* W ==> User Won */
	else if (lives == 0)
	  { game_state = 'L';		/* L ==> User Lost */
            strcpy(part_word, whole_word);	/* Show User the word */
          }
	sprintf(outbuf, " %s   %d\n", part_word, lives);
	write(out, outbuf, strlen(outbuf));
      }
}
