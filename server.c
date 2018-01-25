#include "networking.h"
#include "fxn.c"

void parse_command(char cmd[], int i, char ** deck, int size, int players[]);

int main(int argc, char **argv) {
  int num_players = 0;

  if (argc < 2) {
    printf("Invalid arguments.\n");
    exit(1);
  }
  else {
    sscanf(argv[1], "%d", &num_players);
  }

  int listen_socket, i = 0, j;
  int players[num_players], subservers[num_players];
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
    subservers[i] = fork();
    if (!subservers[i]) {
      close(players[i]);
      return 0;
    }
    i++;
  }
  printf("Server is no longer accepting players.\n");
  shutdown(listen_socket, SHUT_RD);

  //set up players
  char buffer[BUFFER_SIZE];
  for (i = 0; i < num_players; i++) {
    snprintf(buffer, sizeof(buffer), "You are player #%d.", i);
    write(players[i], buffer, sizeof(buffer));
  }

  //set up deck
  int size;

  printf("\nCreating Deck\n");
  char ** deck = create_deck(2, &size);

  printf("\nShuffling Deck\n\n");
  shuffle(deck, size);
  
  while(1) {
    for (i = 0; i < num_players; i++) {
      write(players[i], ACK, sizeof(ACK));
      read(players[i], buffer, sizeof(buffer));
      parse_command(buffer, i, deck, size, players);
      printf("%s\n", buffer);
      for (j = 0; j < num_players; j++) write(players[j], buffer, sizeof(buffer));
    }
  }
}

//does stuff based on command used
void parse_command(char cmd[], int i, char ** deck, int size, int players[])
{
  //printf("%d\n", strcmp(cmd, "draw"));
  if(!strcmp(cmd, "draw"))
    {
      char card[16];
      printf("drawing...\n");
      strcpy(card, draw_card(deck, &size));
      write(players[i], card, sizeof(card));
      sprintf(cmd, "[msg]:Player %d drew a card.", i);
    }
  else
    {
      cmd = "no command";
    }
}

