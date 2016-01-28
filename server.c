#include "server.h"

int main() {
  int socket_id, socket_client;
  card* deck;

  socket_id=socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in listener;
  bzero((char *) &listener, sizeof(listener));
  listener.sin_family = AF_INET;
  listener.sin_port=htons(24601);
  listener.sin_addr.s_addr=INADDR_ANY;
  int binder = bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  if (binder < 0) {
    printf("%s\n", strerror(errno));
    exit(1);
  }
  listen(socket_id, 5);
  
  while (1) {
    printf("<server> listening for player connection\n");
    socket_client=accept(socket_id, NULL, NULL);
    if (socket_client<0) {
      printf("%s",strerror(errno));
    } 
    int pid = fork();
    if (pid<0) {
      printf("%s",strerror(errno));
    } 
    if (pid==0) {
      close(socket_id);
      printf("<server> connected to player\n");
      deck = make_deck( deck );
      play(socket_client,deck);
      free_deck(deck);
      exit(0);
    }
    else {
      close(socket_client);
      free_deck(deck);
    }
  }
  return 0;
}

void play (int socket_client, card* deck) {
  char* user_input;
  int number_of_players;
  int number_of_cards;
  int player_index;
  int current_player_score;
  int highest_player_score;
  int is_end;
  int ace_choice;
  card* current_card;
  card* cycle_card;
  

  number_of_players = 2;
  
  number_of_cards = 52; //NUMBER OF CARDS AT THE START
  
  //Player/Dealer arrays
  card players[2];
  
  //start game
  deal( players, number_of_cards, deck );
  printf("dealt it\n");
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
    bzero(p_response,256);
    hands = print_hand(&players[0], &players[1]);
    printf("hands: %s\n", hands);
    //write the first round of hands
    write(socket_client, hands, strlen(hands)+1);
    sleep(3);

    //first choice of hit or stand
    read(socket_client, p_response, 255);
    strtok(p_response, "\n");
    printf("Read %s from client\n", p_response);
    p_score = sum(&players[1]);
    while (strcmp(p_response, "1") && !strcmp(p_response, "0") && 
	   p_score<21) {
      printf("presponse is [%s]\n", p_response);
      bzero(p_response,256);
      printf("entered if\n");
      player_last->next_card = hit( players, number_of_cards, 
				    deck, player_index, player_last );
      printf("updated hands with hit after player chose\n");
      player_last = player_last -> next_card;
      hands = print_hand(&players[0], &players[1]);
      printf("new hands: %s\n", hands);
	
      write(socket_client, hands, strlen(hands)+1);
      sleep(5);
      read(socket_client, p_response, 255);
      strtok(p_response, "\n");
      printf("Read %s from client\n", p_response);
      p_score = sum(&players[1]);
      /*while (!p_response) {
	sleep(2);
	read(socket_client, p_response, 255);
	strtok(p_response, "\n");
	}*/
    } 
    /*if (strcmp(p_response, "1")) {
      printf("client took too long....\n");
      break;
      }*/
    if (p_score>21) {
      printf("p_score>21\n");
      break;
    } else if (p_score==21) {
      printf("p_score==21\n");
      break;
    } else {
      player_index = 0;
      d_score = sum(&players[0]);
      while( d_score < 17 ) {
	printf("%s\n", print_hand(&players[0],&players[1]));
	dealer_last->next_card = hit( players, number_of_cards, 
				      deck, player_index, dealer_last );
	printf("dealer hit\n");
	dealer_last = dealer_last->next_card;
	d_score = sum(&players[0]);
	}
    }
    //write(socket_client, players, sizeof(players));
    printf("p:%d, d:%d\n",p_score,d_score);
    win = winner( p_score, d_score );
    printf("time to send the scores\n");
    char *buff = (char *)malloc(sizeof(char)*256);
    sprintf(buff, "Dealer's score: %d\nYour score: %d\n", d_score, p_score);
    sleep(1);
    //sprintf(buff,"%d", win);
    write(socket_client, buff, strlen(buff)+1);
    printf("sent scores\n");
    buff[0]='\n';
    p_response[0]='\n';
    read(socket_client, p_response, 10);
    printf("p_response: %s\n", p_response);
    sprintf(buff,"%d", win);
    sleep(3);
    write(socket_client, buff, strlen(buff)+1);
    printf("sent win\n");
    free(buff);
    break;
  }
}




      
    

