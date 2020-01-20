OBJS	= main.o morpion.o
SOURCE	= main.c morpion.c
HEADER	= morpion.h
OUT	= main.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = `sdl-config --cflags --libs` -lSDL_mixer -lSDL_ttf

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

morpion.o: morpion.c
	$(CC) $(FLAGS) morpion.c 


clean:
	rm -f $(OBJS) $(OUT)