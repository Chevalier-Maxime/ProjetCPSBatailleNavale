CC = gcc
STRUCT = ./src/structureDonnee.h ./src/affichage.h ./src/jouer.h ./src/remplir.h
SRCS = ./src/structureDonnee.c ./src/affichage.c ./src/jouer.c ./src/remplir.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -fPIC -DNMAX=200 -I ./src
EXEC = ./bin/BatailleNavale

all : $(EXEC)

$(EXEC) : ./src/main.o 
	$(CC) ./src/main.o -o $(EXEC)

clean:
	-rm -rf ./src/*.o


