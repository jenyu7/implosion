#include "networking.h"
#include "fxn.c"

int main(int argc, char **argv) {

  int server_socket, player_number, deck_size, hand_size, current_player, next_player, num_players;
  char buffer[BUFFER_SIZE];
  char ** deck;
  char ** hand;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf("Waiting for all players to connect.\n");

  memset(buffer, 0, BUFFER_SIZE);
  read(server_socket, buffer, sizeof(buffer));
  printf("%s\n", buffer);
  sscanf(buffer, "You are player %d.", &player_number);

  memset(buffer, 0, BUFFER_SIZE);
  read(server_socket, buffer, sizeof(buffer));
  deck_size = atoi(buffer);
  printf("deck size: %d\n", deck_size);
  memset(buffer, 0, BUFFER_SIZE);
  read(server_socket, buffer, sizeof(buffer));
  deck = string_to_deck(buffer);
  printf("\n\ndeck\n\n");
  print_deck(deck, deck_size);
  hand = create_hand(deck, &deck_size, &hand_size);
  printf("\n\nhand\n\n");
  print_deck(hand, hand_size);
  printf("\n\ndeck\n\n");
  print_deck(deck, deck_size);

  memset(buffer, 0, BUFFER_SIZE);
  sprintf(buffer, "%d", deck_size);
  write(server_socket, buffer, sizeof(buffer));

  memset(buffer, 0, BUFFER_SIZE);
  strcpy(buffer, deck_to_string(deck, deck_size));
  printf("%s\n", buffer);
  write(server_socket, buffer, sizeof(buffer));

  int f = 0;
  while (f--) {
    printf("Waiting for your turn.\n");
    while (1) {
      read(server_socket, buffer, sizeof(buffer));
      if (strcmp(buffer, ACK)) {
        printf("received: [%s]\n", buffer);
      }
      else break;
    }
    printf("my turn\n");
    read(server_socket, buffer, sizeof(buffer));
    deck_size = atoi(buffer);
    printf("%d\n", deck_size);
    /* read(server_socket, buffer, sizeof(buffer)); */
    /* deck = string_to_deck(buffer); */
    /* read(server_socket, buffer, sizeof(buffer)); */
    /* num_players = atoi(buffer); */
    /* read(server_socket, buffer, sizeof(buffer)); */
    /* int * player_list; */
    /* player_list = string_to_players(buffer, num_players); */
    /* read(server_socket, buffer, sizeof(buffer)); */
    /* current_player = atoi(buffer); */
    /* read(server_socket, buffer, sizeof(buffer)); */
    /* next_player = atoi(buffer); */
    /* print_deck(hand, hand_size); */

    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    //process the stuff
    //snprintf(buffer, sizeof(buffer), "%d-%s-%s-%d-%d", deck_size, deck_to_string(deck, deck_size), player_string, current_player, next_player);
    write(server_socket, buffer, sizeof(buffer));
  }
}
