#include "networking.h"
#include "fxn.c"

char * get_card_name(char ** catalog, int id);
char ** create_catalog(int* size);
int get_card_id(char * card);

char ** create_catalog(int* size){
  *size = 12;
  char ** catalog = calloc(*size, sizeof(char *));
  catalog[0] = "Defuse";
  catalog[1] = "Attack";
  catalog[2] = "Shuffle";
  catalog[3] = "Alter The Future";
  catalog[4] = "See The Future";
  catalog[5] = "Skip";
  catalog[6] = "Catermelon";
  catalog[7] = "Beard Cat";
  catalog[8] = "Tacocat";
  catalog[9] = "Hairy Potato Cat";
  catalog[10] = "Rainbow Ralphing Cat";
  catalog[11] = "Exploding Kitten";
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
  int size = 0;
  int hand[51];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf("Waiting for all players to connect.\n");
  read(server_socket, buffer, sizeof(buffer));
  hand[size++] = 1;
  char * cards = calloc(250, sizeof(char));
  strcpy(cards, buffer);
  int i;
  for (i = 0; i < 4; i++) {
    char * tmp = strsep(&cards, "-");
    hand[size++] = atoi(tmp);
  }

  while (1) {
    printf("Waiting for your turn.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      if (strcmp(buffer, ACK)) {
        printf("received: [%s]\n", buffer);
      }
      else break;
    }
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    
    *strchr(buffer, '\n') = 0;

    if (strcmp(buffer, "draw") != 0) {
      // Change index to card name
      int pos = atoi(buffer);
      //printf("\nCARD: %s\n", get_card_name(catalog,pos));
      strcpy(buffer, get_card_name(catalog,hand[pos]));

      
      write(server_socket, buffer, sizeof(buffer));
      memset(buffer, 0, BUFFER_SIZE);
      read(server_socket, buffer, sizeof(buffer));
      printf("buffer:%s\n", buffer);
      int id = atoi(buffer);
      printf("cardid:%d\n", id);
      hand[size] = id;
      size--;
    } else {
      write(server_socket, buffer, sizeof(buffer));
      memset(buffer, 0, BUFFER_SIZE);
      read(server_socket, buffer, sizeof(buffer));
      printf("buffer:%s\n", buffer);
      int id = atoi(buffer);
      printf("here\n");
      printf("cardid:%d\n", id);
      hand[size] = id;
      size++;
      printf("Card name:%s\n",get_card_name(catalog, id) );
      char * name = calloc(50, sizeof(char));
      name = get_card_name(catalog, id);
      sprintf(buffer, "Drew the %s card.", name);
      printf("%s\n", buffer);

      // Exploding Kitten Check
      if (strcmp(name, "Exploding Kitten") == 0) {
	// Check if player has a defuse
	int i = 0;
	for (i = 0; i < size; i++) {
	  if (hand[i] == 0) {
	    
	    // Write defuse to server
	    strcpy(buffer, get_card_name(catalog,hand[i]));

	    write(server_socket, buffer, sizeof(buffer));
	    memset(buffer, 0, BUFFER_SIZE);
	    read(server_socket, buffer, sizeof(buffer));
	    printf("buffer:%s\n", buffer);
	    int id = atoi(buffer);
	    printf("cardid:%d\n", id);
	    hand[size] = id;
	    size--;

	    // Ask player where to put kitten
	    printf("\nHow many cards do you want to place the kitten under?\n");
	    fgets(buffer, sizeof(buffer), stdin);
	    *strchr(buffer, '\n') = 0;
	    write(server_socket, buffer, sizeof(buffer));
	    memset(buffer, 0, BUFFER_SIZE);
	  }
	}
	printf("\n=========YOU DIED========\n");
	// Handle Death
	strcpy(buffer, "Dead");
	write(server_socket, buffer, sizeof(buffer));
	memset(buffer, 0, BUFFER_SIZE);
	exit(0);
      }
    }
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
