#include "header.h"

// Deck
// 38 + exploding = total_cards
// exploding_kittens = players - 1
// 1 DEFUSE in deck
// 5 NOPE
// 4 ATTACK
// 4 SKIP
// 4 FAVOR
// 4 SHUFFLE
// 4 SEE THE FUTURE
// 4 TACOCAT, 4 RAINBOW-RALPHING CAT, 4 HAIRY POTATO CAT

char ** create_deck(int players) {
  printf("Creating deck...\n");
  int i, pos, exploding_kittens, total_cards;
  pos = 0;
  exploding_kittens = players - 1;
  total_cards = 38 + exploding_kittens;
 
  char ** deck = calloc(total_cards, sizeof(char *));
  printf("after calloc\n");
  
  for (i = 0; i < 4; i++) {
    printf("Pre-attack\n");
    printf("pos: %d\n", pos);
    // Attack
    strcpy(deck[pos], "Attack"); // SEGFAULT
    pos++;
    printf("pos: %d\n", pos);
    // Skip
    strcpy(deck[pos], "Skip");
    pos++;
    // Favor
    strcpy(deck[pos], "Favor");
    pos++;
    // Shuffle
    strcpy(deck[pos], "Shuffle");
    pos++;
    // See The Future
    strcpy(deck[pos], "See The Future");
    pos++;
    // Tacocat
    strcpy(deck[pos], "Tacocat");
    pos++;
    // Rainbow-ralphing Cat
    strcpy(deck[pos], "Rainbow-ralphing Cat");
    pos++;
    // Hairy Potato Cat
    strcpy(deck[pos], "Hairy Potato Cat");
    pos++;
  }
  
  for (i = 0; i < 5; i++) {
    // Nope
    strcpy(deck[pos], "Nope");
    pos++;
  }

  for (i = 0; i < exploding_kittens; i++) {
    // Exploding Kitten
    strcpy(deck[pos], "Exploding Kitten");
    pos++;
  }

  // Defuse
  strcpy(deck[pos], "Defuse");
  
  return deck;
}

int main() {

  printf("main...\n");
  create_deck(2);

  return 0;

}
