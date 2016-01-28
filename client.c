#include "client.h"

void play(the_sock) {
  char user_in[256];
  char* score = (char *)malloc(sizeof(char)*256);
  char* hands = (char *)malloc(sizeof(char)*256);
  int hand_val;
  int i;
  
  printf("\n------------ Welcome to Blackjack! ---------------\n");
  printf("\n------------ Let's start the game! -----------\n");
  printf("\n------ The game has begun. The dealer will now deal. --------\n");
  sleep(3);
  printf("\n------------ The dealer had dealt. -----------\n");
  read(the_sock, hands, 30);
  printf("read result: %s\n",hands);
  if (i<0) {
    printf("error: %s\n", strerror(errno));
    free(score);
    free(hands);
    return;
  }
  printf("Dealer Hand: %s\n", strsep(&hands,","));
  printf("Your Hand: %s\n", hands);
  printf("\n---------- What'll it be then, eh? ---------\n");
  printf("Choose one:\n");
  printf("0: Hit\n1: Stand\n");
  fgets(user_in, sizeof(user_in), stdin);
  printf("<client> just chose %s\n", user_in);
  //strsep(&hands,":");
  
  //write initial hit/stand to server
  write(the_sock, user_in, sizeof(user_in));
  strtok(user_in, "\n");
  while (strcmp(user_in, "1")) { //hit
    user_in[0]='\n';
    hands[0]='\n';
    sleep(1);
    printf("\n------------ You have been hit! -----------\n");
    read(the_sock, hands, 30);
    printf("Dealer Hand:%s\n", strsep(&hands, ","));
    printf("Your Hand:%s\n", hands);
    strsep(&hands,":");
    printf("~~%d~~\n",atoi(hands));
    if (hands && atoi(hands)==21) {
      //printf("won");
      printf("You win :)))))))\n");
      free(score);
      free(hands);
      return;
    } else if (hands && atoi(hands)>21) {
      printf("Dealer wins ;-;\n");
      free(score);
      free(hands);
      return;
    }
    printf("Choose one:\n");
    printf("0: Hit\n1: Stand\n");
    fgets(user_in, sizeof(user_in), stdin);
    printf("<client> just chose %s\n", user_in);
    write(the_sock, user_in, sizeof(user_in));
  }

  printf("\n------- You chose to stand. Dealer deals to itself. -------\n");
  sleep(2);
  printf("\n--------- Game over! Here's the score: --------\n");
  read(the_sock, score, 80);
  printf("%s\n", score);
  char* resp="OK";
  write(the_sock, resp, sizeof(resp));
  char* win = (char *)malloc(sizeof(char)*256);
  read(the_sock, win, 10);
  printf("win: %s\n", win);
  if (!strcmp("0",win)) {
    printf("Dealer wins ;-;\n");
  } else if (!strcmp("1",win)) {
    printf("You win :)))))))\n");
  }
  //free(win);
  free(score);
  free(hands);
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
  //printf("mid\n");
  printf("SOCKET ID: %i\n", socket_id); 
  play(socket_id);
  
  return 0;
}
