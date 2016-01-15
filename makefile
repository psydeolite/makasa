all: main.o client.o server.o chat.o
	gcc -o main.o server.o chat.o client.o blackjack

main: main.c main.h
	gcc -c main.c 

client: client.c client.h
	gcc -c client.c

server: server.c server.h
	gcc -c server.c

chat: chat.c chat.h
	gcc -c chat.c

run: blackjack
	./blackjack

clean:
	rm -f *~
	rm -f *#
	rm -f *.o

