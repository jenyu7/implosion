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
  int players[num_players], subservers[num_players], turns[num_players];
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
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

  int deck_size;
  //Creates deck
  char ** deck = create_deck(num_players, &deck_size);
  //Shuffles deck
  shuffle(deck, deck_size);

  //setup players
  for (i = 0; i < num_players; i++) {
    snprintf(buffer, sizeof(buffer), "%d-%d-%d-%d", get_card_id(draw_card(deck, &deck_size)), get_card_id(draw_card(deck, &deck_size)), get_card_id(draw_card(deck, &deck_size)), get_card_id(draw_card(deck, &deck_size)));
    write(players[i], buffer, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "You are player #%d", i);
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);
  }
  add_kittens(deck, num_players, &deck_size);
  shuffle(deck, deck_size);

  memset(buffer, 0, BUFFER_SIZE);


  while(1) {
    for (i = 0; i < num_players; i++) {
      turns[i] += 1;
      while (turns[i]) {
        write(players[i], ACK, sizeof(ACK));
        read(players[i], buffer, sizeof(buffer));
        if(strcmp(buffer, "draw") == 0) {
          char card[50];
          strcpy(card, draw_card(deck, &deck_size));
          printf("%s\n", card);
          char card_id[8];
          sprintf(card_id, "%d", get_card_id(card));
          printf("cardid:%s\n", card_id);
          write(players[i], card_id, sizeof(card_id));
          sprintf(buffer, "Player %d drew a card.", i);
	  if (strcmp(buffer, "Exploding Kitten") != 0) {
	    turns[i] -= 1;
	  }
          
        } else if (strcmp(buffer, "Attack") == 0) {
          printf("Play Attack\n");
          turns[i] = 0;

          int index = (i + 1) % num_players;
          turns[index] += 1;

          sprintf(buffer, "You attacked Player %d!", index);
          write(players[i], buffer, sizeof(buffer));
          sprintf(buffer, "Player %d attacked Player %d", i, index);
        } else if (strcmp(buffer, "Shuffle") == 0) {
          printf("Play Shuffle\n");
          shuffle(deck, deck_size);
          strcpy(buffer, "You shuffled the deck!");
          write(players[i], buffer, sizeof(buffer));
          sprintf(buffer, "Player %d shuffled the deck!", i);
        } else if (strcmp(buffer, "Alter The Future") == 0) {
          printf("Play Alter The Future\n");
          alter_the_future(deck);
          strcpy(buffer, "You altered the future!");
          write(players[i], buffer, sizeof(buffer));
          sprintf(buffer, "Player %d altered the future!", i);
        } else if (strcmp(buffer, "See The Future") == 0) {
          printf("Play See The Future\n");
          strcpy(buffer, see_the_future(deck));
          write(players[i], buffer, sizeof(buffer));
          sprintf(buffer, "Player %d saw the future!", i);
        } else if (strcmp(buffer, "Skip") == 0) {
          printf("Play Skip\n");
          turns[i] -= 1;
          strcpy(buffer, "You skipped your turn!");
          write(players[i], buffer, sizeof(buffer));
          sprintf(buffer, "Player %d skipped his turn!", i);
        } else if (strcmp(buffer, "double") == 0) {
          printf("Played a double card combo!\n");
          char card[50];
          strcpy(card, draw_random_card(deck, &deck_size));
          printf("%s\n", card);
          char card_id[8];
          sprintf(card_id, "%d", get_card_id(card));
          printf("cardid:%s\n", card_id);
          write(players[i], card_id, sizeof(card_id));
          sprintf(buffer, "Player %d drew a card.", i);
        } else if (strcmp(buffer, "Dead") == 0) {
          printf("Player %d has died!", i);
          sprintf(buffer, "Player %d has died!", i);
          // Remove player from array and decrement num_players
          //int j;
          //for (j = num_players; j > 0;
          num_players -= 1;

          if (num_players == 1) {
            sprintf(buffer, "Player %d has won the game!", players[0]);
          }
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
  else if (strcmp(card, "Alter The Future") == 0)
    return 4;
  else if (strcmp(card, "See The Future") == 0)
    return 5;
  else if (strcmp(card, "Skip") == 0)
    return 6;
  else if (strcmp(card, "Catermelon") == 0)
    return 7;
  else if (strcmp(card, "Beard Cat") == 0)
    return 8;
  else if (strcmp(card, "Tacocat") == 0)
    return 9;
  else if (strcmp(card, "Hairy Potato Cat") == 0)
    return 10;
  else if (strcmp(card, "Rainbow Ralphing Cat") == 0)
    return 11;
  else if (strcmp(card, "Exploding Kitten") == 0)
    return 12;
  else
    return 0;
}

/*
  sprintf(buffer, "%d", deck_size);
  write(players[i], buffer, sizeof(buffer));
 else if (strcmp(buffer, "Defuse") == 0) {
          printf("Play Defuse\n");
          sprintf(buffer, "Player %d defused the exploding kitten!", i);
	  write(players[i], buffer, sizeof(buffer));
	  
          //strcpy(buffer, "How many cards do you want to place the kitten under?");
          read(players[i], buffer, sizeof(buffer));
	  turns[i] = 0;
        }
*/
