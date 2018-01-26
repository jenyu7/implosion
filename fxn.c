#include "header.h"

int add_cards(char ** deck, char * card_name, int amount, int pos){
  for(;amount-->0;) deck[pos++] = card_name;
  return pos;
}

char ** create_deck(int players, int * deck_size) {
  int pos = 0;
  *deck_size = 47 - players;
  char ** deck = calloc(51, sizeof(char *));

  pos = add_cards(deck, "Attack", 4, pos);
  pos = add_cards(deck, "Skip", 4, pos);
  pos = add_cards(deck, "Favor", 4, pos);
  pos = add_cards(deck, "Shuffle", 4, pos);
  pos = add_cards(deck, "See The Future", 5, pos);
  pos = add_cards(deck, "Tacocat", 4, pos);
  pos = add_cards(deck, "Rainbow Ralphing Cat", 4, pos);
  pos = add_cards(deck, "Hairy Potato Cat", 4, pos);
  pos = add_cards(deck, "Catermelon", 4, pos);
  pos = add_cards(deck, "Beard Cat", 4, pos);
  //pos = add_cards(deck, "Nope", 5, pos);
  pos = add_cards(deck, "Defuse", 6 - players, pos);
  //pos = add_cards(deck, "Exploding Kitten", players - 1, pos);

  return deck;
}

void add_kittens(char ** deck, int players, int * deck_size){
  add_cards(deck, "Exploding Kitten", players-1, *deck_size);
  *deck_size = *deck_size + players -1;
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

/* char * play_card(char ** deck, int deck_size, char ** hand, int * hand_size, int pos) { */
/*   char * card = hand[pos]; */
/*   memmove(&hand[pos], &hand[pos+1], ((*hand_size)--) * sizeof(char *)); */
/*   hand[*hand_size] = 0; */
/*   return card; */
/* } */

char * see_the_future(char ** deck) {
  char * buffer = calloc(1000, sizeof(char));
  int i;
  for (i = 0; i < 3; i++) {
    char tmp[500];
    printf("Card %d: %s\n", i + 1, deck[i]);
    sprintf(tmp, "Card %d: %s\n", i + 1, deck[i]);
    strcat(buffer, tmp);
  }
  return buffer;
}

void alter_the_future(char ** deck) {
  shuffle(deck, 3);
}


char * draw_card(char ** deck, int * size) {
  char * ret = deck[0];
  memmove(deck, &deck[1], (--*size) * sizeof(ret));
  deck[*size] = 0;
  return ret;
}

void insert_card(char ** deck, int * size, char * card, int pos) {
  memmove(&deck[pos+1], &deck[pos], ((*size)++ - pos) * sizeof(char *));
  deck[pos] = card;
}

void skip() {

}

void defuse(char ** deck, int * size, int pos) {
  insert_card(deck, size, "Exploding Kitten", pos);
}

void attack() {

}

void favor() {

}

char * deck_to_string(char ** deck, int size) {
  char * ret = calloc(size*17, sizeof(char));
  int i;
  for( i=0; i<size; i++) {
    strcat(ret, deck[i]);
    strcat(ret, ",");
  }
  *strrchr(ret, ',') = 0;
  return ret;
}

char ** string_to_deck(char * s) {
  int size = 51;
  char ** deck = calloc(51, sizeof(char *));
  int pos = 0;
  for ( ; size-- > 0; ) {
    pos = add_cards(deck, strsep(&s, ","), 1, pos);
  }
  return deck;
}

char * players_to_string( int * player_list, int size ){
  char * ret = calloc(size*2, sizeof(char));
  int i;
  for ( i=0; i<size; i++) {
    char player[1];
    sprintf(player, "%d", player_list[i]);
    strcat(ret, player);
    strcat(ret, ",");
  }
  *strrchr(ret, ',') = 0;
  return ret;
}

int * string_to_players( char * s, int size ) {
  int * ret = calloc(size, sizeof(int));
  int pos;
  for (pos = 0 ; pos < size; pos++ ) {
    int player;
    sscanf(strsep(&s,","), "%d", &player);
    ret[pos] = player;
  }
  return ret;
}

char ** create_hand(char ** deck, int * deck_size, int * hand_size) {
  int pos = 0;
  char ** hand = calloc(51, sizeof(char *));
  int i;
  pos = add_cards(hand, "Defuse", 1, pos);
  for(i=0; i < 4; i++) {
    pos = add_cards(hand, draw_card(deck, deck_size), 1, pos);
  }
  *hand_size = 5;
  return hand;
}


/* int main() { */

/*   int size; */

/*   printf("\nCreating Deck\n"); */
/*   char ** deck = create_deck(2, &size); */
/*   print_deck(deck, size); */

/*   printf("\nShuffling Deck\n"); */
/*   shuffle(deck, size); */
/*   print_deck(deck, size); */

/*   /\* printf("\nTesting See The Future\n"); *\/ */
/*   /\* see_the_future(deck); *\/ */

/*   /\* printf("\nTesting draw_card\n"); *\/ */
/*   /\* printf("Drew the card \"%s\"\n", draw_card(deck, &size)); *\/ */
/*   /\* print_deck(deck,size); *\/ */

/*   /\* printf("\nTesting insert_card\n"); *\/ */
/*   /\* insert_card(deck, &size, "INSERT_CARD", 5); *\/ */
/*   /\* print_deck(deck,size); *\/ */

/*   char * deck_string = deck_to_string(deck, size); */

/*   printf("\n%s\n\n", deck_string); */

/*   char ** deck2 = string_to_deck(deck_string); */

/*   print_deck(deck2, 51); */

/*   int hand_size; */
/*   char ** hand = create_hand(deck2, &size, &hand_size); */
/*   printf("\n\nprinting deck\n\n"); */
/*   print_deck(deck, size); */

/*   printf("\n\nprinting hand\n\n"); */
/*   print_deck(hand, hand_size); */

/*   printf("\n\nprinting deck\n\n"); */
/*   print_deck(deck, size); */

/*   free(deck); */
/*   return 0; */

/* } */
