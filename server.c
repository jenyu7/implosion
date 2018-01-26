#include "networking.h"
#include "fxn.c"

int get_card_id(char * card);

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
  int players[num_players], subservers[num_players], player_list[num_players], turns[num_players];
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
    player_list[i] = i;
    turns[i] = 0;
    subservers[i] = fork();
    if (!subservers[i]) {
      close(players[i]);
      return 0;
    }
    i++;
  }
  printf("Server is no longer accepting players.\n");
  shutdown(listen_socket, SHUT_RD);
  char buffer[BUFFER_SIZE];
  
  //setup players
  for (i = 0; i < num_players; i++) {
    snprintf(buffer, sizeof(buffer), "You are player #%d", i);
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);
  }
  memset(buffer, 0, BUFFER_SIZE);
  
  int deck_size;
  //Creates deck
  char ** deck = create_deck(num_players, &deck_size);
  //Shuffles deck
  shuffle(deck, deck_size);
  
  while(1) {
    for (i = 0; i < num_players; i++) {
      turns[i] += 1;
      while (turns[i]) {
	write(players[i], ACK, sizeof(ACK));
	read(players[i], buffer, sizeof(buffer));
	if(strcmp(buffer, "draw") == 0)
	  {
	    char card[50];
	    strcpy(card, draw_card(deck, &deck_size));
	    printf("%s\n", card);
	    char card_id[8];
	    sprintf(card_id, "%d", get_card_id(card));
	    printf("cardid:%s\n", card_id);
	    write(players[i], card_id, sizeof(card_id));
	    sprintf(buffer, "Player %d drew a card.", i);
	    turns[i] -= 1;
	  }
	for (j = 0; j < num_players; j++)
	  if (j != i)
	    write(players[j], buffer, sizeof(buffer));
      }
    }
  }
}


int get_card_id(char * card){
  if (strcmp(card, "Defuse") == 0)
    return 1;
  else if (strcmp(card, "Attack") == 0)
    return 2;
  else if (strcmp(card, "Shuffle") == 0)
    return 3;
  else if (strcmp(card, "Favor") == 0)
    return 4;
  else if (strcmp(card, "See The Future") == 0)
    return 5;
  else if (strcmp(card, "Reverse") == 0)
    return 6;
  else if (strcmp(card, "Skip") == 0)
    return 7;
  else if (strcmp(card, "Catermelon") == 0)
    return 8;
  else if (strcmp(card, "Beard Cat") == 0)
    return 9;
  else if (strcmp(card, "Tacocat") == 0)
    return 10;
  else if (strcmp(card, "Hairy Potato Cat") == 0)
    return 11;
  else if (strcmp(card, "Rainbow Ralphing Cat") == 0)
    return 12;
  else
    return 0;
}

/*
      sprintf(buffer, "%d", deck_size);
      write(players[i], buffer, sizeof(buffer));
 */
