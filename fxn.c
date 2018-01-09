#include "header.h"

// Deck
// 4 ATTACK
// 4 SKIP
// 4 FAVOR
// 4 SHUFFLE
// 5 SEE THE FUTURE
// 4 TACOCAT
// 4 RAINBOW-RALPHING CAT
// 4 HAIRY POTATO CAT
// 5 NOPE
// 6 - players = DEFUSE
// players - 1 EXPLODNG KITTENS

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

void swap(char * a, char * b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void shuffle(char ** deck, int size) {
  srand(time(NULL));
  int r = rand();
  int i, j;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < size; j++) {
      int pos = rand() % size;
      swap(&deck[i], &deck[pos]);
    }
  }
}

void see_the_future(char ** deck) {
  int i;
  for (i = 0; i < 3; i++) {
    printf("Card %d: %s\n", i + 1, deck[i]);
  }
}


int main() {

  int size;
  char ** deck = create_deck(2, &size);
  print_deck(deck, size);
  
  shuffle(deck, size);
  
  see_the_future(deck);
  print_deck(deck, size);
  
  free(deck);
  return 0;

}
