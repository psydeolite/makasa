all: 
	dealer
	server
	client

client: client.c client.h 
	gcc client.c -o client

server: server.c dealer
	gcc server.c dealer.o -o server 

dealer: dealer.c dealer.h
	gcc -c dealer.c

clean:
	rm -f *~
	rm -f *#
	rm -f *.o
	rm -f server
	rm -f client
	rm -rf server.dYSM
