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
  
    int socket_id, socket_client;
  
  socket_id=socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port=htons(24601);
  listener.sin_addr.s_addr=INADDR_ANY;
  int binder = bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  if (binder < 0) {
      printf("%s\n", strerror(errno));
      exit(1);
  }
  listen(socket_id, 1);
  
  while (1) {
    struct sockaddr_in clientAddress;
    printf("<server> listening for player connection\n");
    printf("SOCKEY ID: %i\n", socket_id);
    socket_client=accept(socket_id, NULL, NULL);
    if (socket_client < 0) {
      printf("%s\n", strerror(errno));
      exit(1);
    }
    printf("<server> connected to player\n");

    number_of_players = 2;

    //printf("pre-makedeck\n");
    deck = make_deck( deck );
    //printf("post-makedeck\n");
    number_of_cards = 52; //NUMBER OF CARDS AT THE START

    //Player/Dealer arrays
    card players[2];
    
    //start game
    deal( players, number_of_cards, deck );
    //printf("dealt it\n");
    card* player_last = players[1].next_card;
    card* dealer_last = players[0].next_card;
    
    char* d_hand;
    char* p_hand;
    char* hands;

    int p_score;
    int d_score;
    int win;
    player_index = 1; //starting from first player

    while (1) {
      char p_response[256]; 
      //continue game
      hands = print_hand(&players[0], &players[1]);
      printf("hands: %s\n", hands);
      write(socket_client, hands, strlen(hands)+1);
      read(socket_client, p_response, 255);
      strtok(p_response, "\n");
      printf("Read %s from client\n", p_response);
      p_score = sum(&players[1]);
      while (!strcmp(p_response, "0") && p_score<21) {
	printf("entered if\n");
	player_last->next_card = hit( players, number_of_cards, deck, player_index, player_last );
	player_last = player_last -> next_card;
	hands = print_hand(&players[0], &players[1]);
	printf("hands: %s\n", hands);
	write(socket_client, hands, strlen(hands)+1);
	read(socket_client, p_response, 255);
	strtok(p_response, "\n");
	printf("Read %s from client\n", p_response);
	p_score = sum(&players[1]);
      } 
      if (p_score>21) {
	win = winner( p_score, d_score );
	break;
      } else if (p_score==21) {
	win = winner( p_score, d_score );
	break;
      } else {
	player_index = 0;
	d_score = sum(&players[0]);
	while( d_score < 17 ) {
	  printf("%s\n", print_hand(&players[0],&players[1]));
	  //printf("%s\n", dealer_last->name);
	  dealer_last->next_card = hit( players, number_of_cards, 
					deck, player_index, dealer_last );
	  dealer_last = dealer_last->next_card;
	  d_score = sum(&players[0]);
	}
	write(socket_client, players, sizeof(players));
	printf("p:%d, d:%d\n",p_score,d_score);
	win = winner( p_score, d_score );
	char *buff = (char *)malloc(sizeof(char)*256);
	sprintf(buff,"%d", win);
	write(socket_client, buff, sizeof(win));
	break;
      }
    }
  }
  return 0;
}




      
    

