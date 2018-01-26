#include "networking.h"
#include "fxn.c"

char * get_card_name(char ** catalog, int id);
char ** create_catalog(int* size);
int get_card_id(char * card);

char ** create_catalog(int* size){
  *size = 13;
  char ** catalog = calloc(*size, sizeof(char *));
  catalog[0] = "Defuse";
  catalog[1] = "Attack";
  catalog[2] = "Shuffle";
  catalog[3] = "Favor";
  catalog[4] = "See The Future";
  catalog[5] = "Reverse";
  catalog[6] = "Skip";
  catalog[7] = "Catermelon";
  catalog[8] = "Beard Cat";
  catalog[9] = "Tacocat";
  catalog[10] = "Hairy Potato Cat";
  catalog[11] = "Rainbow Ralphing Cat";
  return catalog;
}

char * get_card_name(char ** catalog, int id){
  return catalog[id-1];
}

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];
  int cat_size;
  char ** catalog = create_catalog(&cat_size);
  int size;
  int hand[51];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf("Waiting for all players to connect.\n");

  while (1) {
    printf("Waiting for your turn.\n");
    while (1) {
      read(server_socket, buffer, sizeof(buffer));
      if (strcmp(buffer, ACK)) {
        printf("received: [%s]\n", buffer);
      }
      else break;
    }
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);
    read(server_socket, buffer, sizeof(buffer));
    printf("buffer:%s\n", buffer);
    int id = atoi(buffer);
    printf("here\n");
    printf("cardid:%d\n", id);
    hand[size] = id;
    size ++;
    printf("Card name:%s\n",get_card_name(catalog, id) );
    char * name = get_card_name(catalog, id);
    sprintf(buffer, "Drew the %s card.", name);
    printf("%s\n", buffer);
  }
}



/*
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
*/
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
    //process the stuff
    //snprintf(buffer, sizeof(buffer), "%d-%s-%s-%d-%d", deck_size, deck_to_string(deck, deck_size), player_string, current_player, next_player);


/*
    printf("my turn\n");
    read(server_socket, buffer, sizeof(buffer));
    deck_size = atoi(buffer);
    printf("%d\n", deck_size);

    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));*/
