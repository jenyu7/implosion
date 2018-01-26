#include "networking.h"
#include "fxn.c"

void process(char *s);
void subserver(int from_client);

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
  int players[num_players], subservers[num_players], player_list[num_players];
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
    player_list[i] = i;
    subservers[i] = fork();
    if (!subservers[i]) {
      close(players[i]);
      return 0;
    }
    i++;
  }
  printf("Server is no longer accepting players.\n");
  shutdown(listen_socket, SHUT_RD);
  int deck_size;
  char ** deck = create_deck(num_players, &deck_size);
  shuffle(deck, deck_size);
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  int current_player = player_list[0];
  int next_player = player_list[1];

  for (i = 0; i < num_players; i++) {
    snprintf(buffer, sizeof(buffer), "You are player #%d", i);
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);

    sprintf(buffer, "%d", deck_size);
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);

    strcpy(buffer, deck_to_string(deck, deck_size));
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);


    read(players[i], buffer, sizeof(buffer));
    deck_size = atoi(buffer);
    printf("deck size: %d\n", deck_size);
    printf("%d\n", deck_size);

    memset(buffer, 0, BUFFER_SIZE);
    read(players[i], buffer, sizeof(buffer));
    deck = string_to_deck(buffer);
    printf("\n\ndeck\n\n");
    print_deck(deck, deck_size);


  }
  int f = 0;
  while(f--) {
    for (i = 0; i < num_players; i++) {
      write(players[i], ACK, sizeof(ACK));
      sprintf(buffer, "%d", deck_size);
      write(players[i], buffer, sizeof(buffer));

      /* strcpy(buffer, deck_to_string(deck, deck_size)); */
      /* write(players[i], buffer, sizeof(buffer)); */
      /* sprintf(buffer, "%d", num_players); */
      /* write(players[i], buffer, sizeof(buffer)); */
      /* strcpy(buffer, players_to_string(player_list, num_players)); */
      /* write(players[i], buffer, sizeof(buffer)); */
      /* sprintf(buffer, "%d", current_player); */
      /* write(players[i], buffer, sizeof(buffer)); */
      /* sprintf(buffer, "%d", next_player); */
      /* write(players[i], buffer, sizeof(buffer)); */

      read(players[i], buffer, sizeof(buffer));
      //for (j = 0; j < num_players; j++) write(players[j], buffer, sizeof(buffer));
    }
  }
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
