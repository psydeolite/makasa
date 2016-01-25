#include "dealer.h"

card* make_card( int value, char* name, int is_ace, card* c) {
  c = malloc( sizeof(card) );
  c -> value = value;
  c -> name = name;
  c -> is_ace = is_ace;

  return c;
}

void make_deck( card* deck) {
  /* Aces to Kings, up the suits (Diamond, Club, Heart, Spade) */
  int counter = 0;
  int value, is_ace;
  char suits[4] = "DCHS"; //diamond, clubs, hearts, spades

  card* current_card = deck;
  card* previous_card = deck;
  //Aces
  value = 1;
  is_ace = 1;
  char* name = "A";
  while( counter < 4) {
    make_card( value, name + suits[counter], is_ace, current_card);
    previous_card = current_card;
    current_card = current_card -> next_card;
    
    counter++;
  }
  //2 to 10
  value++; // value == 2
  is_ace = 0; 
  while( value <= 10) {
    counter = 0;
    while( counter < 4) {
      //converts integer value to string, base 10
      itoa( value, name, 10);
      
      make_card( value, name + suits[counter], is_ace, current_card);
      previous_card = current_card;
      current_card = current_card -> next_card;

      counter++;
    }
    value++;
  }
  //Jack, Queen, King
  while( value <= 13) {
    counter = 0;
    while( counter < 4 ) {
      if( value == 11) { //Jacks
	name = "J";
	make_card( value, name + suits[counter], is_ace, current_card);
      } else if( value == 12) { //Queens
	name = "Q";
	make_card( value, name + suits[counter], is_ace, current_card);
      } else if(value == 13) { //Kings
	name = "K";
	make_card( value, name + suits[counter], is_ace, current_card);
      }

      previous_card = current_card;
      current_card = current_card -> next_card;

      counter++;
    }
    value++;
  }}

int deal( card* players, int number_of_cards, card* deck ) {
  printf("-------- The game has begun. The dealer will now deal. -----------");
  ;

  //Dealer (hide second card in graphics only)
  players[0] = *random_card( deck, number_of_cards );
  players[0].next_card = random_card( deck, number_of_cards );
 
}

card* random_card( card* deck, int number_of_cards ) {
  srand(time(NULL));
  int r = rand() % number_of_cards;

  card* current_card = deck;
  card* previous_card = deck;
  //cycles to a random card
  while( r > 0 ) {
    previous_card = current_card;
    current_card = current_card -> next_card;
    r--;
  }
  //re-links and returns the card
  previous_card -> next_card = current_card -> next_card;
  number_of_cards--;
  
  return current_card;
}

void stand( int highest_player_score, int dealer_score ) {
  if( highest_player_score > dealer_score )
    printf("The player has won!");
  else if( dealer_score > highest_player_score)
    printf("The dealer has won!");
  else
    printf("It is a tie.");
}

int main() {
  printf("\n------------ Welcome to Blackjack! ---------------\n");

  //Number of players ( <= 4 )
  printf("\n How many players want to play?");
  char* user_input = malloc( 256 );
  /*user_input in the form of #, for both choice (hit/stand) and for # of players ==> use atoi() to convert */
  user_input = fgets( user_input, 256, stdin );

  user_input[ strlen( user_input ) - 1] = 0; //truncate \n
  int number_of_players = atoi( user_input ); //convert to int
  
  //Make the deck
  card* deck;
  make_deck( deck );
  int number_of_cards = 52; //NUMBER OF CARDS AT THE START

  
  //Player/Dealer arrays
  card players[ number_of_players + 1 ] = malloc( sizeof(card) * number_of_players );


  //start game
  printf("\n------------ Let's start the game! -----------\n");
  deal( players, number_of_cards, deck );

  
  /*
  int socket_id, socket_client;

  socket_id=socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port=htons(24601);
  listener.sin_addr.s_addr=INADDR_ANY;
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));

  listen(socket_id, 1);
  printf("<server> listenin\n");
  
  while (1==1) {
    socket_client=accept(socket_id, NULL, NULL);

    int p=fork();
    if (!p) {
      printf("<server> connected: %d\n", socket_client);
      write(socket_client, "ayy", 4);
    }
    }
  */

  return 1;
}
