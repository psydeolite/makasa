#include "dealer.h"

card* make_card( int value, char cname[], int is_ace, card* c) {
  //printf("!!%s!!\n", cname);
  //printf("!!%s!!\n", c -> name);
  c = (card *)malloc( sizeof(card) );
  c -> value = value;
  c -> name = (char *)malloc( 256*sizeof(char) );
  strcpy(c -> name, cname);
  c -> is_ace = is_ace;
  c -> next_card = NULL;
  
  return c;
}

card* make_deck( card* current_card ) {
  /* Aces to Kings, up the suits (Diamond, Club, Heart, Spade) */
  int counter = 0;
  int value, is_ace;
  char suits[4] = "DCHS"; //diamond, clubs, hearts, spades
 
  card* deck;
  card* deck2;
  //card* previous_card = deck;
  //Aces
  value = 1;
  is_ace = 1;
  char* name = "A";
  while( counter < 4 ) {
    char nom[256];
    nom[0] = *name;
    nom[1] = suits[counter];
    nom[2] = '\0';
    
    //deck = make_card( value, nom, is_ace, current_card);
      //printf("%s\n", deck -> name);
      //current_card = deck -> next_card;
    //} else {
    current_card = make_card( value, nom, is_ace, current_card);
      //printf("%s\n", deck -> next_card -> name);
      
    if (counter == 0) {
      deck = current_card;
    }
    if (counter == 1) {
      deck -> next_card = current_card;
      deck2 = deck -> next_card;
    } else {
      deck2 -> next_card = current_card;
      deck2 = deck2 -> next_card;
    }
    //printf("%p %s\n", current_card, current_card->name);
    //printf("%p %s\n", deck -> next_card, deck->name);
    current_card = current_card -> next_card;

    counter++;
  }

  //2 to 9
  value++; // value == 2
  is_ace = 0; 
  while( value <= 9) {
    counter = 0;
    while( counter < 4) {
      //converts integer value to string, base 10
      char name[256];
      char *nom;
      sprintf( &name[0], "%d", value );
      name[1] = suits[counter];
      name[2] = '\0';
      current_card = make_card( value, name, is_ace, current_card);
      //previous_card = current_card;
      deck2 -> next_card = current_card;
      deck2 = deck2 -> next_card;
      current_card = current_card -> next_card;
      //printf("%s", deck -> next_card -> name);
      counter++;
    }
    value++;
  }

  //10
  counter = 0;
  while( counter < 4) {
    //converts integer value to string, base 10
    char name[256];
    char *nom;
    sprintf( &name[0], "%d", value );
    name[2] = suits[counter];
    name[3] = '\0';
    current_card = make_card( value, name, is_ace, current_card);
    //previous_card = current_card;
    deck2 -> next_card = current_card;
    deck2 = deck2 -> next_card;
    current_card = current_card -> next_card;  
    counter++;
  }
  value++;

  //Jack, Queen, King
  while( value <= 13) {
    counter = 0;
    //printf("j");
    while( counter < 4 ) {
      char name[265];
      name[1] = suits[counter];
      name[2] = '\0';
      if( value == 11) { //Jacks
	name[0] = 'J';
	current_card = make_card( 10, name, is_ace, current_card);
      } else if( value == 12) { //Queens
	name[0] = 'Q';
	current_card = make_card( 10, name, is_ace, current_card);
      } else if(value == 13) { //Kings
	name[0] = 'K';
	current_card = make_card( 10, name, is_ace, current_card);
      }
      //previous_card = current_card;
      deck2 -> next_card = current_card;
      deck2 = deck2 -> next_card;
      current_card = current_card -> next_card;

      counter++;
    }
    value++;
  }
  return deck;
}

int deal( card* players, int number_of_cards, card* deck ) {
  int i = 0;
  //Dealer + Players (hide second card in graphics only for dealer)
  while( i < 2 ) {
    players[i] = *random_card( deck, number_of_cards );
    number_of_cards--;
    players[i].next_card = random_card( deck, number_of_cards );
    number_of_cards--;
    //printf("%s\n",players[i].next_card->name);
    i++;
  }
  return number_of_cards;
}

card* random_card( card* deck, int number_of_cards ) {
  srand(time(NULL));
  int r = rand() % number_of_cards;
  if (r==number_of_cards-1) {
    r--;
  }
  card* current_card = deck;
  card* previous_card = deck;
  //cycles to a random card
  while( r > 1 ) {
    //previous_card = current_card;
    current_card = current_card -> next_card;
    r--;
  }
  card* ret = current_card->next_card;
  //re-links and returns the card
  current_card -> next_card = current_card -> next_card -> next_card;
  //number_of_cards--;
  ret->next_card = NULL;
  return ret;
}

//char* hit( card* players, int number_of_cards, card* deck, int player_index) {

char* print_hand( card* hand1, card* hand2 ) {
  char* result = (char *)malloc(256*sizeof(char));
  while (hand1) {
    strcat(result,hand1->name);
    strcat(result," ");
    hand1 = hand1 -> next_card;
  }
  strcat(result,",");
  while (hand2) {
    strcat(result,hand2->name);
    strcat(result," ");
    hand2 = hand2 -> next_card;
  }
  return result;
}

card* hit( card* players, int number_of_cards, card* deck, int player_index, card* last_card) {
  card* current_card = random_card( deck, number_of_cards );
  last_card->next_card = current_card;
  number_of_cards--;

  //return current_card;
  return current_card;
}

int stand( int number_of_players, int player_index ) {
  if( player_index == 0 ) //dealer, end game
    return -1;
  else 
    player_index++;

  //If last player, go to dealer
  if( player_index > number_of_players )
    return 0;
  else
    return player_index;
}

int dealer_score( card* players ) {
  int score;
  int ace_counter;
  card* current_card;
  
  current_card = &players[0];
  while( current_card != NULL ) {
    score += current_card -> value;	
    current_card = current_card -> next_card;
  }

  return score;
}


int player_score( card* players, int player_index ) {

  int score;
  card* current_card;
  
  current_card = &players[0];
  while( current_card != NULL ) {
    score += current_card -> value; //add to score
    
    current_card = current_card -> next_card; //next card
  }

  return score;
}

void end_game( int highest_player_score, int dealer_score ) {
  if( highest_player_score > dealer_score )
    printf("The player has won!");
  else if( dealer_score > highest_player_score)
    printf("The dealer has won!");
  else
    printf("It is a tie.");
}

