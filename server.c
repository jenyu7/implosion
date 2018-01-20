#include "networking.h"

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
  int players[num_players], subservers[num_players];
  listen_socket = server_setup();

  while (i < num_players) {
    players[i] = server_connect(listen_socket);
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
  for (i = 0; i < num_players; i++) {
    snprintf(buffer, sizeof(buffer), "You are player #%d", i);
    write(players[i], buffer, sizeof(buffer));
  }
  while(1) {
    for (i = 0; i < num_players; i++) {
      write(players[i], ACK, sizeof(ACK));
      read(players[i], buffer, sizeof(buffer));
      process(buffer);
      for (j = 0; j < num_players; j++) write(players[j], buffer, sizeof(buffer));
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
