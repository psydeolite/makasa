#ifndef DEALER_H
#define DEALER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

typedef struct card {
  int value;
  int is_ace;
  char* name;
  
  struct card* next_card;
} card; 

#endif

/* --------------------------
Makes individial card

Input: Value (Ace is one by default), String name, is_ace (0 or 1)

Output: Pointer to card struct

*/
card* make_card( int value, char* name, int is_ace, card* c);


/* ------------------------------------
Generates deck of standard playing cards (52 unique cards, A-K, four suits) for use during gameplay
Only run once when starting new games (in main)

 - Deck is a linked list referenced through the "first card" of the linked list. 

 - Loops through value-suit (e.g. Ace of Diamonds, Ace of Clubs... King of Hearts, King of Diamonds)

 - Last card of deck points to null

Input: First card, declared in main

Output: Array of card structs referenced through the master array "deck"
*/
void make_deck( card* deck); 



/* ---------------------------------------------
Initates game and gives player and dealer cards

Input: N/A
Returns: Dealer's hidden card
*/
card* deal(); 



/* ---------------------------------------
Get random card from deck and remove it from the deck, using random( <total number of current deck cards)

Input: "deck": first card of the deck (linked list)
Output: Random card struct
*/
card* random_card( card* deck, int num_of_cards ); 



/* --------------------------------------
Dealer stops and finishes game.

Input: The highest score from among the players
Output: Game over status and result, as dealer is last to play
*/
int stand( int highest_player_score );

