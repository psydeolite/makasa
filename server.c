#include "server.h"

int main() {
  char* user_input;
  int number_of_players;
  int number_of_cards;
  int player_index;
  int current_player_score;
  int highest_player_score;
  int d_score;
  int is_end;
  int ace_choice;
  card* deck;
  card* current_card;
  card* cycle_card;
  
  printf("\n------------ Welcome to Blackjack! ---------------\n");

  int socket_id, socket_client;
  
  socket_id=socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port=htons(24601);
  listener.sin_addr.s_addr=INADDR_ANY;
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  listen(socket_id, 1);
  
  
  while (1) {
    struct sockaddr_in clientAddress;
    printf("<server> listening for player connection\n");
    socket_client=accept(socket_id, NULL, NULL);
    printf("<server> connected to player\n");

    //Number of players ( <= 4 )
    //printf("\n How many players want to play?: ");
    //user_input = malloc( 256 );
    /*user_input in the form of #, for both choice (hit/stand) and for # of players ==> use atoi() to convert */
    /*user_input = fgets( user_input, 256, stdin );
      printf("input: %s\n", user_input);
      user_input[ strlen( user_input ) - 1] = 0; //truncate \n
      number_of_players = atoi( user_input ); //convert to int */
    
    number_of_players = 1;
  
    deck = make_deck( deck );
    number_of_cards = 52; //NUMBER OF CARDS AT THE START

    //Player/Dealer arrays
    number_of_players++; //for dealer
    card players[2];

    //start game
    printf("\n------------ Let's start the game! -----------\n");
    
    printf("\n------- The game has begun. The dealer will now deal. ---------\n");
    deal( players, number_of_cards, deck, number_of_players );
    card* player_last = players[1].next_card;
    card* dealer_last = dealers[1].next_card;
 
    player_index = 1; //starting from first player

    while (1) {
      char p_response[256]; 
      //continue game
      
      write(socket_client, players, sizeof(players));
      
      read(socket_client, p_response, 255);
      
      if(!strcmp(p_response, "0")) {
	current_card = hit( players, number_of_cards, deck, player_index, player_last );
	player_last = player_last -> next_card;
      } else {
	player_index = 0;
	break;
      }
    }
    /*
      DEALER'S TURN (player_index = 0)
      
      Here, the dealer's hidden card is displayed (Katherine). As with before, with each new card, the screen should refresh with new graphical output
    */
    while( d_score < 17 ) {
      hit( players, number_of_cards, deck, player_index, dealer_last );
      dealer_last = dealer_last->next_card;
      d_score = dealer_score( players );
      
      /* Send players array to server/client and refresh graphical output */
      write(socket_client, players, sizeof(players));
    }
    
    //GAME ENDS
    end_game( highest_player_score, d_score ); //both still need to be calculated
  }
  return 0;
}




    //1 is hit code
    //while( player_index < number_of_players && player_index > 0 ) {
    /* 
       PLAYER'S CHOICES HERE, DEALER IS BELOW:
       
       Everyone's card info is transmitted to each player here, first card of dealer is hidden at this point. Each player makes their decisions and calls hit() or stand() accordingly.
       
       ***I took the liberty of writing stand below***
       Just add an if condition for when the right input

       Once the last player stands, it will break out of the while loop and go to the dealer. See below for more info

       Also, if card is an ace, make the player decide whether to have it as a 1 or 11. 1 is default.
     */
      //current_card = hit( players, number_of_cards, deck, player_index );
      //if( current_card -> is_ace == 1) { // ace
      //	write(socket_client, "ace", 2);
      //	while (read(socket_client, p_response, 255)) {
      //	  printf("Received [%s] from client\n", p_response);
      //	}
      //	if (!strcmp(p_response, "0")) {
      //	  ace_choice=1;
      //	} else if (!strcmp(p_response, "1")) {
      //	  ace_choice=11;
      //	}
      
      /* Make player choose 1 or 11 here using int "ace_choice"
	 If player chooses one, don't change ace_choice.
      */
      
      /* Change ace_choice here if applicable */
      
      //	if( ace_choice == 11 ) {
      //	  cycle_card = players[ player_index ];
      //	  while( cycle_card != current_card )
      //	    cycle_card = cycle_card -> next_card;
      //	}
      //}
      //}
      //else {/* player input == stand */
      //	player_index = stand( number_of_players, player_index );
      //}
      
      //current_player_score = player_score( players, player_index - 1);
      //if( current_player_score > highest_player_score )
      // highest_player_score = current_player_score;
      
      /*Send players array to server/client and refresh graphical output */
      //}
      
    

