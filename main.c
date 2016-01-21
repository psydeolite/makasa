#include "main.h"

int main() {
  card* deck; //first card of deck, in linked list
  
  printf("Welcome to Blackjack!");
  printf("Shuffling deck");

  make_deck( deck ); //init deck
  
  return 0;
}
