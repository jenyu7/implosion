#include "networking.h"
#include "fxn.c"

char * get_card_name(char ** catalog, int id);
char ** create_catalog(int* size);
int get_card_id(char * card);
void print_hand(int hand[], int size, char ** catalog);

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
          strcpy(buffer, "double");
	  write(server_socket, buffer, sizeof(buffer));
	  memset(buffer, 0, BUFFER_SIZE);
<<<<<<< HEAD
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
=======
>>>>>>> 7b262096238175c59dfe42fd1cba225b3e8deff9
        }
        else{
          printf("Sorry, but the cards don't match.\n");
	  write(server_socket, buffer, sizeof(buffer));
	  memset(buffer, 0, BUFFER_SIZE);
        }
      }

      //printf("\nCARD: %s\n", get_card_name(catalog,pos));
      strcpy(buffer, get_card_name(catalog,hand[pos]));


      write(server_socket, buffer, sizeof(buffer));
      memset(buffer, 0, BUFFER_SIZE);
      read(server_socket, buffer, sizeof(buffer));
      printf("buffer:%s\n", buffer);
      int id = atoi(buffer);
      printf("cardid:%d\n", id);
      memmove(&hand[pos], &hand[pos+1], ((--size) - pos) * sizeof(int));
      hand[size] = 0;
    }
    else {
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
            printf("\nYou defused the exploding kitten. How many cards do you want to place the kitten under?\n");
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
