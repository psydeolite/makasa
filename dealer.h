#ifndef DEALER
#define DEALER

#include <stdio.h>
#include <stdlib.h>

typedef struct card {
  int value;
  char* name;
  int is_ace;
} card; 

#endif

/* ------------------------------------
Generates deck of standard playing cards (52 unique cards, A-K, four suits) for use during gameplay
Only run once when starting new games (in main)

Output: Array of card structs referenced through the master array "deck"
*/
void make_deck( char** deck); 



/* ---------------------------------------------
Initates game and gives player and dealer cards

Input: N/A
Returns: Dealer's hidden card
*/
card deal(); 



/* ---------------------------------------
Get random card from deck and remove it from the deck

Output: Random card struct
*/
card random_card(); 



/* --------------------------------------
Dealer stops and finishes game.

Output: Game over status and result, as dealer is last to play
*/
int stand();

