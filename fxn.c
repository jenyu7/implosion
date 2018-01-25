#include "header.h"

int add_cards(char ** deck, char * card_name, int amount, int pos){
  for(;amount-->0;) deck[pos++] = card_name;
  return pos;
}

char ** create_deck(int players, int * deck_size) {
  int pos = 0;
  *deck_size = 51;
  char ** deck = calloc(*deck_size, sizeof(char *));

  pos = add_cards(deck, "Attack", 4, pos);
  pos = add_cards(deck, "Skip", 4, pos);
  pos = add_cards(deck, "Favor", 4, pos);
  pos = add_cards(deck, "Shuffle", 4, pos);
  pos = add_cards(deck, "See The Future", 5, pos);
  pos = add_cards(deck, "Tacocat", 4, pos);
  pos = add_cards(deck, "Rainbow-ralphing Cat", 4, pos);
  pos = add_cards(deck, "Hairy Potato Cat", 4, pos);
  pos = add_cards(deck, "Catermelon", 4, pos);
  pos = add_cards(deck, "Beard Cat", 4, pos);
  pos = add_cards(deck, "Nope", 5, pos);
  pos = add_cards(deck, "Defuse", 6 - players, pos);
  pos = add_cards(deck, "Exploding Kitten", players - 1, pos);

  return deck;
}

void print_deck(char ** deck, int size) {
  int i;
  for(i = 0; i < size; i++) {
    printf("%s\n", deck[i]);
  }
}

void shuffle ( char ** deck, int size ) {
  srand ( time(NULL) );
  for (; size-- > 1;) {
    int i = rand() % (size+1);
    char * tmp = deck[i];
    deck[i] = deck[size];
    deck[size] = tmp;
  }
}

void see_the_future(char ** deck) {
  int i;
  for (i = 0; i < 3; i++) {
    printf("Card %d: %s\n", i + 1, deck[i]);
  }
}

char * draw_card(char ** deck, int * size) {
  char * ret = deck[0];
  memmove(deck, &deck[1], (--*size) * sizeof(ret));
  deck[*size] = 0;
  return ret;
}

void insert_card(char ** deck, int * size, char * card, int pos) {
  memmove(&deck[pos+1], &deck[pos], ((*size)++ - pos) * sizeof(char *));
  deck[5] = card;
}

int main() {

  int size;

  printf("\nCreating Deck\n");
  char ** deck = create_deck(2, &size);
  print_deck(deck, size);

  printf("\nShuffling Deck\n");
  shuffle(deck, size);
  print_deck(deck, size);

  printf("\nTesting See The Future\n");
  see_the_future(deck);

  printf("\nTesting draw_card\n");
  printf("Drew the card \"%s\"\n", draw_card(deck, &size));
  print_deck(deck,size);

  printf("\nTesting insert_card\n");
  insert_card(deck, &size, "THIS_CARD_WAS_INSERTED_______", 5);
  print_deck(deck,size);

  free(deck);
  return 0;

}
