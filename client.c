#include "client.h"

void play(the_sock) {
  char user_in[256];
  char* dealer = (char *)malloc(sizeof(char)*256);
  char* player = (char *)malloc(sizeof(char)*256);
  char* hands = (char *)malloc(sizeof(char)*256);
  // char* d_hand=(char*)malloc(sizeof(char)*256);
  //char* p_hand=(char*)malloc(sizeof(char)*256);
  int hand_val;
  int i;
  //char c[256];
  //char char2[256];
  
  
  while (1==1) {
    printf("\n-------------- Welcome to Blackjack! ----------------\n");
    //printf("inside play loop\n");
    //printf("%d\n", read(the_sock, user_in, sizeof(user_in)));
    //i=read(the_sock, d_hand, sizeof(d_hand));
    //printf("read d_result:_%s_\n",d_hand);
    //char* resp="OK";
    //write(the_sock, resp, sizeof(resp));
    //printf("size of phand: %d\n", sizeof(p_hand));
    //read(the_sock, p_hand, strlen(p_hand)+1);
    //printf("read p_result:_%s_\n",p_hand);

    printf("\n-------------- Let's start the game! --------------\n");
    //sleep(50);
    printf("\n-------------- The game has begun. The dealer will now deal. --------------\n");
    i=read(the_sock, hands, 14);
    //printf("read result: %s\n", hands);
    if (i<0) {
      printf("error: %s\n", strerror(errno));
      exit(1);
    }
    sleep(5);
    printf("\n-------------- The dealer has dealt.--------------\n");
    printf("Dealer Hand:%s\n", strsep(&hands,","));
    printf("Your Hand:%s\n\n", hands);
    printf("\n-------------- What'll it be then, eh? --------------\n");
    printf("Choose one:\n");
    printf("0: Hit\n1: Stand\n");
    //user_in[0]='\0';
    
    fgets(user_in, sizeof(user_in), stdin);
    //printf("<client> just chose %s\n", user_in);

    write(the_sock, user_in, sizeof(user_in));
    printf("sent first choice to server!\n");

    sleep(100);
    //&deal[0]=NULL;
    char res[256];
    //dealer sends some shit back; if player hit, sends another card
    //if player stand sends back winner?
    if (!strcmp(user_in, "0")) { //hit
      //read(the_sock, dealer, sizeof(dealer));
      //read(the_sock, player, sizeof(player));
      printf("-------------- You will be hit. --------------\n");
      read(the_sock, res, sizeof(res));
      printf("res: %s\n", res);
      printf("Dealer Hand:%s\n", dealer);
      printf("Your Hand:%s\n", player);
      printf("Choose one:\n");
      printf("0: Hit\n1:Stand\n");
      
      fgets(user_in, sizeof(user_in), stdin);

      write(the_sock, user_in, sizeof(user_in));
    } else {
      //deal[0]='\0';
      printf("Game over! Here's the score:\n");
      read(the_sock, dealer, sizeof(dealer));
      printf("%s\n", dealer);
    }
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
