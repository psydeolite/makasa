#include "client.h"

void play(the_sock) {
  char user_in[256];
  char deal[256];
  int hand_val;
  int i;
  while (1==1) {
    read(the_sock, deal, sizeof(user_in));
    printf("<client> received [%s] from server\n", deal);
    printf("Choose one:\n");
    printf("0: Hit\n1:Stand\n");
    //user_in[0]='\0';
    
    fgets(user_in, sizeof(user_in), stdin);
    printf("<client> just chose %s\n", user_in);

    write(the_sock, user_in, sizeof(user_in));

    deal[0]='\0';
    //dealer sends some shit back; if player hit, sends another card
    //if player stand sends back winner?
    read(the_sock, deal, sizeof(deal));
    
    
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

  i=connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);

  while (1) {
    read(socket_id, buffer, sizeof(buffer));
    printf("<client> received: [%s]\n", buffer);
    //flush(buffer);
    buffer[0]='\0';

    printf("Choose one:\n");
    printf("0: Hit\n");
    printf("1: Stand\n");
    fgets(buffer, sizeof(buffer), stdin);
    printf("input: %s\n", buffer);
    write(
    
  }

  return 0;
}
