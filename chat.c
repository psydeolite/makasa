#include "chat.h"
#include "dealer.h"

typedef struct card {
  int value;
  int is_ace;
  char* name;

  struct card* next_card;
} card;

//functions
/*void parse_in(char input[]) {
  if (!strcmp(input, "1")) {
    
  } else if (!strcmp(input, "2")) {
    //stand
  } else if (!strcmp(input, "3")) {
    //chat
  } else {
    printf("Invalid input innit bruv\n");
  }
  }*/

//takes user's hand, new card dealt, and boolean determining usage of ace
//returns value of the card, to be added to user total in main
int hit(card* hand, card new, int is_one) {
  int to_add=card->value;
  if (is_ace) {
    if (!is_one) {
      to_add=11;
    }
  }
  hand->next_card=new;
  return to_add;
}

//networking involved
void chat() {}
  
  

