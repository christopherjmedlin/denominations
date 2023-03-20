cflags = $(shell pkg-config --cflags gtk+-3.0)
libs = $(shell pkg-config --libs gtk+-3.0) -lm

denoms : main.o gui.o denoms.o
	gcc $(cflags) -o denoms main.o gui.o denoms.o $(libs)

main.o : main.c
	gcc $(cflags) -c main.c $(libs)

gui.o : gui.c
	gcc $(cflags) -c gui.c $(libs)

denoms.o : denoms.c
	gcc $(cflags) -c denoms.c $(libs)
