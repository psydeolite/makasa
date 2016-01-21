#ifndef DEALER_H
#define DEALER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct card {
  int value;
  char* name;
  int is_ace;
  struct card* next_card;
} card; 

#endif

/* --------------------------
Makes individial card

Input: Value (Ace is one by default), String name, is_ace (0 or 1), and pointer to next card.

Output: Card struct

*/
card make_card( int value, char* name, int is_ace, card* next_card );

/* ------------------------------------
Generates deck of standard playing cards (52 unique cards, A-K, four suits) for use during gameplay
Only run once when starting new games (in main)

 - Deck is a linked list referenced through the "first card" of the linked list. 

 - Loops through value-suit, so Ace of Diamonds, Ace of Clubs ... Two of Diamonds, Two of Clubs ... King of Spades

 - Last card of deck points to null

Input: First card, declared in main

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
Get random card from deck and remove it from the deck, using random( <total number of current deck cards)

Output: Random card struct
*/
card random_card(); 



/* --------------------------------------
Dealer stops and finishes game.

Output: Game over status and result, as dealer is last to play
*/
int stand();

