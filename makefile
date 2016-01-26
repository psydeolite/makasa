all: ./dealer ./player
	playr
	dealr

playr: player.c player.h 
	gcc player.c -o player

dealr: dealer.c control.o
	gcc dealer.c control.o -o dealer

control: control.c control.h
	gcc -c control.c

clean:
	rm -f *~
	rm -f *#
	rm -f *.o

