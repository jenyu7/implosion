#include "networking.h"

int main(int argc, char **argv) {

  int server_socket, player_number;
  char buffer[BUFFER_SIZE];

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
    printf("received: [%s]\n", buffer);
  }
}
