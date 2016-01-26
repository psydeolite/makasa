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

int deal( card* players, int number_of_cards, card* deck, int number_of_players ) {
  printf("-------- The game has begun. The dealer will now deal. -----------");
  ;
  int i = 0;
  //Dealer + Players (hide second card in graphics only for dealer)
  while( i < number_of_players ) {
    players[i] = *random_card( number_of_cards );
    players[i].next_card = random_card( number_of_cards );
    number_of_cards--;
    i--;
  }
  return number_of_cards;
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

card* hit( card* players, int number_of_cards, card* deck, int player_index) {
  card* current_card = random_card( deck, number_of_cards );
  players[ player_index ] = *current_card;
  number_of_cards--;

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
  //dealer
  if( player_index == 0 ) {
    current_card = &players[0];
    while( current_card != NULL ) {
      if( current_card -> is_ace == 0) //not ace
	score += current_card -> value;	
      else //ace
	ace_counter++;
      current_card = current_card -> next_card;
    }
    while( ace_counter > 0 ) {
      if( score < 11 )
	score += 11;
      else
	score++;
      ace_counter--;
    }
  }
}

void end_game( int highest_player_score, int dealer_score ) {
  if( highest_player_score > dealer_score )
    printf("The player has won!");
  else if( dealer_score > highest_player_score)
    printf("The dealer has won!");
  else
    printf("It is a tie.");
}

int main() {
  char* user_input;
  int number_of_players;
  int number_of_cards;
  int player_index;
  int highest_player_score;
  int dealer_score;
  int is_end;
  card* deck;
  
  
  printf("\n------------ Welcome to Blackjack! ---------------\n");

  //Number of players ( <= 4 )
  printf("\n How many players want to play?");
  user_input = malloc( 256 );
  /*user_input in the form of #, for both choice (hit/stand) and for # of players ==> use atoi() to convert */
  user_input = fgets( user_input, 256, stdin );

  user_input[ strlen( user_input ) - 1] = 0; //truncate \n
  number_of_players = atoi( user_input ); //convert to int
  
  //Make the deck
  make_deck( deck );
  number_of_cards = 52; //NUMBER OF CARDS AT THE START

  
  //Player/Dealer arrays
  number_of_players++; //for dealer
  card players[ number_of_players ] = malloc( sizeof(card) * number_of_players );


  //start game
  printf("\n------------ Let's start the game! -----------\n");
  deal( players, number_of_cards, deck, number_of_players );

  //continue game
  player_index = 1; //starting from first player
  while( player_index < number_of_players && player_index > 0 ) {
    /* 
       RUN GAME
       YOU CAN CALL HIT AND STAND HERE
       INCREMENT player_turn 
     */

    player_index = stand( number_of_players, player_index );
  }
  
  player_index = 0;
  //DEALER'S TURN (player_index = 0)
  while( dealer_score < 17 ) {
    hit( players, number_of_cards, deck, player_index );
    dealer_score = dealer_score( players );
  }
  
  end_game( highest_player_score, dealer_score ); //both still need to be calculated

  
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
