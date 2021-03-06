#include "networking.h"
#include "fxn.c"

char * get_card_name(char ** catalog, int id);
char ** create_catalog(int* size);
int get_card_id(char * card);
void print_hand(int hand[], int size, char ** catalog);
void remove_card_from_hand(int hand[], int pos, int * size);

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

int check_buffer(char * buffer, int size, int hand[]){
  if (strcmp(buffer, "draw") == 0)
    return 0;
  else if (strcmp(buffer, "print") == 0)
    return 0;
  else{
    int i = atoi(buffer);
    if (i == 0)
      return 1;
    else{
      if (i > size-1)
	return 1;
      else if (hand[i] == 0)
	return 1;
      else
	return 0;
      
    }
  }
}

int defuse(int hand[], int size){
  int i;
  for (i = 0; i < size; i ++){
    if (hand[i] == 1)
      return i+1;
  }
  return 0;
}

char * get_card_name(char ** catalog, int id){
  return catalog[id-1];
}

void print_hand(int hand[], int size, char ** catalog){
  int i;
  //char * out = get_card_name(catalog, hand[0]);
  for (i = 0; i < size; i ++){
    printf("%d: %s\n", i, get_card_name(catalog, hand[i]));
    //sprintf(out, ":%s:%d", out, hand[i]);
  }
  //printf("Current hand - %s\n", out);
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

  printf("\n\nWelcome to Exploding Kittens!\nView your hand by typing 'print'\nType 'draw' to draw a card and end your turn.\nSelect action cards to play by specifying the index (i.e. 0).\nYour goal is to be the last human alive by using your action cards to survive.\n\n");
  while (1) {
    printf("Waiting for your turn.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      if (strcmp(buffer, ACK)) {
        printf("received: [%s]\n", buffer);
      }
      else break;
    }
    while(check_buffer(buffer, size, hand)){
      printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
    }

    if (strcmp(buffer, "print") == 0){
      print_hand(hand, size, catalog);
      write(server_socket, buffer, sizeof(buffer));
      memset(buffer, 0, BUFFER_SIZE);
    }
    else if (strcmp(buffer, "draw") != 0) {
      // Change index to card name
      int pos = atoi(buffer);
      if(hand[pos] > 6){
        int next;
        printf("Index of other cat card: ");
        fgets(buffer, sizeof(buffer), stdin);
        next = atoi(buffer);
        if(hand[next] == hand[pos]){
          remove_card_from_hand(hand, next, &size);
          remove_card_from_hand(hand, pos, &size);
          strcpy(buffer, "double");
          write(server_socket, buffer, sizeof(buffer));
          memset(buffer, 0, BUFFER_SIZE);
          read(server_socket, buffer, sizeof(buffer));
          int id = atoi(buffer);
          printf("Card name: %s\n",get_card_name(catalog, id) );
          char * name = calloc(50, sizeof(char));
          name = get_card_name(catalog, id);
          printf("Drew the %s card.\n", name);
	  if (strcmp(name, "Exploding Kitten")){
	    memset(buffer, 0, BUFFER_SIZE);
	    strcpy(buffer, "drew");
	    write(server_socket, buffer, sizeof(buffer));
	    hand[size] = id;
	    size++;
	  }
	  else{
	    int ind;
	    if (ind = defuse(hand, size)){
	      printf("You defused the bomb!\n");
	      remove_card_from_hand(hand, ind-1, &size);
	      sprintf(buffer, "%s", "Defuse");
	      write(server_socket, buffer, sizeof(buffer));
	      read(server_socket, buffer, sizeof(buffer));
	      printf("How many cards from the top do you want to place the exploding kitten?\n");
	      //printf("%s\n", buffer);
	      sprintf(buffer, "%d", 1);
	      while(atoi(buffer)){
		printf("Please choose a number greater than 0.\n");
		fgets(buffer, sizeof(buffer), stdin);
	      }
	      write(server_socket, buffer, sizeof(buffer));
	      
	    }
	    else{
	      sprintf(buffer, "%s", "dead");
	      write(server_socket, buffer, sizeof(buffer));
	      read(server_socket, buffer, sizeof(buffer));
	      //printf("%s\n", buffer);
	      exit(0);
	    }
	  }
        }
        else{
          printf("Sorry, but the cards don't match.\n");
          write(server_socket, buffer, sizeof(buffer));
          memset(buffer, 0, BUFFER_SIZE);
        }
      }
      else {
        //printf("\nCard: %s\n", get_card_name(catalog,pos));
        strcpy(buffer, get_card_name(catalog,hand[pos]));


        write(server_socket, buffer, sizeof(buffer));
        memset(buffer, 0, BUFFER_SIZE);
        read(server_socket, buffer, sizeof(buffer));
        //printf("buffer:%s\n", buffer);
        int id = atoi(buffer);
        remove_card_from_hand(hand, pos, &size);
      }
    }
    else {
      write(server_socket, buffer, sizeof(buffer));
      memset(buffer, 0, BUFFER_SIZE);
      read(server_socket, buffer, sizeof(buffer));
      //printf("buffer:%s\n", buffer);
      int id = atoi(buffer);
      printf("Card name: %s\n",get_card_name(catalog, id) );
      char * name = calloc(50, sizeof(char));
      name = get_card_name(catalog, id);
      sprintf(buffer, "Drew the %s card.\n", name);
      if (strcmp(name, "Exploding Kitten")){
	memset(buffer, 0, BUFFER_SIZE);
	strcpy(buffer, "drew");
	write(server_socket, buffer, sizeof(buffer));
	hand[size] = id;
	size++;
      }
      else{
	int ind;
	printf("defusing..\n");
	if (ind = defuse(hand, size)){
	  printf("You defused the bomb!\n");
	  remove_card_from_hand(hand, ind-1, &size);
	  sprintf(buffer, "%s", "Defuse");
	  write(server_socket, buffer, sizeof(buffer));
	  read(server_socket, buffer, sizeof(buffer));
	  printf("How many cards from the top do you want to place the exploding kitten?\n");
	  while(atoi(buffer)<=0){
	    printf("Please choose a number greater than 0.\n");
	    fgets(buffer, sizeof(buffer), stdin);
	  }
	  write(server_socket, buffer, sizeof(buffer));
	      
	}
	else{
	  sprintf(buffer, "%s", "dead");
	  write(server_socket, buffer, sizeof(buffer));
	  read(server_socket, buffer, sizeof(buffer));
	  exit(0);
	}
      }
    }
  }
}


void remove_card_from_hand(int hand [], int pos, int * size) {
  memmove(&hand[pos], &hand[pos+1], ((--*size) - pos) * sizeof(int));
  hand[*size] = 0;
}

/*
 // Exploding Kitten Check
      if (strcmp(name, "Exploding Kitten") == 0) {
        // Check if player has a defuse
        int i;
        for (i = 0; i < size; i++) {
          if (strcmp(get_card_name(catalog, hand[i]), "Defuse") == 0) {

            printf("DEFUSE FOUND AT [%d]", i);
            // Write defuse to server
            strcpy(buffer, "Defuse");

            write(server_socket, buffer, sizeof(buffer));
            memset(buffer, 0, BUFFER_SIZE);
            read(server_socket, buffer, sizeof(buffer));
            printf("buffer:%s\n", buffer);
            int id = atoi(buffer);
            printf("cardid:%d\n", id);
            remove_card_from_hand(hand, i, &size);

            printf("GET READY TO RUMBLE");

            // Ask player where to put kitten
            printf("\nYou defused the exploding kitten. How many cards do you want to place the kitten under?\n");
            fgets(buffer, sizeof(buffer), stdin);
            *strchr(buffer, '\n') = 0;
            write(server_socket, buffer, sizeof(buffer));
            memset(buffer, 0, BUFFER_SIZE);

            break;
          }
 */
