#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct card {
  int value;
  int is_ace;
  char* name;

  struct card* next_card;
} card;
//headers
//takes user's hand, new card dealt by dealer, boolean determining ace/one
int hit (card* hand, card new, int is_one);


//functions
