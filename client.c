#include "networking.h"

void print_hand(char ** hand, int size) {
  int i;
  for(i = 0; i < size; i++) {
    printf("%s\n", hand[i]);
  }
}

int main(int argc, char **argv) {

  int server_socket, player_number;
  int fd;
  char buffer[BUFFER_SIZE];
  char ** hand = calloc(51, sizeof(char *));
  int hand_size = 0;
  

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf("Waiting for all players to connect.\n");
  read(server_socket, buffer, sizeof(buffer));
  sscanf(buffer, "You are player %d.", &player_number);
  printf("%s\n", buffer);
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
    read(server_socket, buffer, sizeof(buffer));
    if(!strncmp(buffer, "[msg]", 5)){
       printf("received: [%s]\n", buffer);
    }
    else{
      printf("Adding...\n");
      //strcpy(buffer, strstr(buffer,"[msg]"));
      hand[hand_size] = buffer;
      hand_size ++;
      print_hand(hand, hand_size);
    }
  }
}
