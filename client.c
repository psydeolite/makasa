#include "client.h"

void play(the_sock) {
  char user_in[256];
  char* score = (char *)malloc(sizeof(char)*256);
  //char* player = (char *)malloc(sizeof(char)*256);
  char* hands = (char *)malloc(sizeof(char)*256);
  int hand_val;
  int i;
  //char c[256];
  //char char2[256];
  
  while (1) {
    printf("\n------------ Welcome to Blackjack! ---------------\n");
    printf("\n------------ Let's start the game! -----------\n");
    printf("\n------ The game has begun. The dealer will now deal. --------\n");
    sleep(5);
    printf("\n------------ The dealer had dealt. -----------\n");
    read(the_sock, hands, 20);
    printf("read result: %s\n",hands);
    if (i<0) {
      printf("error: %s\n", strerror(errno));
      exit(1);
    }
    printf("Dealer Hand: %s\n", strsep(&hands,","));
    printf("Your Hand: %s\n", hands);
    printf("\n---------- What'll it be then, eh? ---------\n");
    printf("Choose one:\n");
    printf("0: Hit\n1: Stand\n");
    //user_in[0]='\0';
    
    fgets(user_in, sizeof(user_in), stdin);
    printf("<client> just chose %s\n", user_in);

    write(the_sock, user_in, sizeof(user_in));
    printf("sent first choice to server!\n");
    
    //&deal[0]=NULL;
    //dealer sends some shit back; if player hit, sends another card
    //if player stand sends back winner?
    while (!strcmp(user_in, "0")) { //hit
      sleep(10);
      printf("\n------------ You have been hit! -----------\n");
      read(the_sock, hands, 20);
      printf("Dealer Hand:%s\n", strsep(&hands, ","));
      printf("Your Hand:%s\n", hands);
      printf("Choose one:\n");
      printf("0: Hit\n1:Stand\n");
      
      fgets(user_in, sizeof(user_in), stdin);
      write(the_sock, user_in, sizeof(user_in));
    }
    //deal[0]='\0';
    sleep(2);
    printf("Game over! Here's the score:\n");
    read(the_sock, score, sizeof(score));
    printf("%s\n", score);
    break;
  }
}
    
int main() {
  int socket_id;
  char buffer[256];
  int i;
  
  socket_id=socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sock;
  sock.sin_family=AF_INET;
  sock.sin_port = htons(24601);

  inet_aton("127.0.0.1", &(sock.sin_addr));
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  printf("before\n");
  i=connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);
  printf("mid\n");
  printf("SOCKET ID: %i\n", socket_id); 
  play(socket_id);
  
  return 0;
}
