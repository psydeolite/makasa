#include "client.h"

void play(the_sock) {
  char user_in[256];
  char* dealer = (char *)malloc(sizeof(char)*256);
  char* player = (char *)malloc(sizeof(char)*256);
  int hand_val;
  int i;
  //char c[256];
  //char char2[256];
  
  
  while (1==1) {
    printf("inside play loop\n");
    //printf("%d\n", read(the_sock, user_in, sizeof(user_in)));
    i=read(the_sock, dealer, sizeof(dealer));
    printf("read result: %d\n",i);
    if (i<0) {
      printf("error: %s\n", strerror(errno));
      exit(1);
    }
    printf("Dealer Hand:%s\n", dealer);
    printf("Your Hand:%s\n", player);
    
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
    if (!strcmp(user_in, "0")) { //hit
      read(the_sock, dealer, sizeof(dealer));
      read(the_sock, player, sizeof(player));
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
