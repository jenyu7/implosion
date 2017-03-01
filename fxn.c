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
// 6 - players DEFUSE (YOU DON'T ADD DEFUSES TO THE DECK) - only 1 in deck
// players - 1 EXPLODNG KITTENS

int add_cards(char ** deck, char * card_name, int amount, int pos){
  for(;amount-->0;) deck[pos++] = card_name;
  return pos;
}

char ** create_deck(int players, int * deck_size) {
  int pos = 0;
  *deck_size = 38 + (players - 1);
  char ** deck = calloc(*deck_size, sizeof(char *));

  pos = add_cards(deck, "Attack", 4, pos);
  pos = add_cards(deck, "Skip", 4, pos);
  pos = add_cards(deck, "Favor", 4, pos);
  pos = add_cards(deck, "Shuffle", 4, pos);
  pos = add_cards(deck, "See The Future", 5, pos);
  pos = add_cards(deck, "Tacocat", 4, pos);
  pos = add_cards(deck, "Rainbow-ralphing Cat", 4, pos);
  pos = add_cards(deck, "Hairy Potato Cat", 4, pos);
  pos = add_cards(deck, "Nope", 5, pos);
  pos = add_cards(deck, "Defuse", 1, pos);
  pos = add_cards(deck, "Exploding Kitten", players - 1, pos);

  return deck;
}

void print_deck(char ** deck, int size) {
  int i;
  for(i = 0; i < size; i++) printf("%s\n", deck[i]);
}

int main() {

  int size;
  char ** deck = create_deck(2, &size);
  print_deck(deck, size);
  free(deck);
  return 0;

}
