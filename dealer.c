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
  while( counter < 4) { 
    
    
  }
  
}

/*card* deal() {

  
  }

card* random_card() {

  
}

int stand() {

  
}*/

int main() {
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

  return 1;
}
