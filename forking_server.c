#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Enter the amount of players (between 2-6).\nEx: './server 3' to have three players\n");
    return 1;
  }

  int num_players;
  sscanf(argv[1], "%d", &num_players);
  if (num_players < 2 || num_players > 6) {
    printf("Only 2-6 players allowed.\n");
    return 1;
  }

  int listen_socket;
  int f;
  listen_socket = server_setup();

  while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
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
