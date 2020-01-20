OBJS	= main.o morpion_simple.o
SOURCE	= main.c morpion_simple.c
HEADER	= morpion_simple.h
OUT	= a.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = `sdl-config --cflags --libs` -lSDL_mixer -lSDL_ttf

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

morpion.o: main.c
	$(CC) $(FLAGS) main.c 

morpion_simple.o: morpion_simple.c
	$(CC) $(FLAGS) morpion_simple.c 


clean:
	rm -f $(OBJS) $(OUT)