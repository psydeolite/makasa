all: ./dealer ./player
	playr
	dealr

playr: player.c player.h 
	gcc player.c player.h -o player

dealr: dealer.c dealer.h control.o
	gcc dealer.c dealer.h control.o -o dealer

control: control.c control.h
	gcc -c control.c control.h

clean:
	rm -f *~
	rm -f *#
	rm -f *.o

