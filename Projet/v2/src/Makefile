CC = gcc
OBJS = structureDonnee.o remplir.o affichage.o jouer.o main.o
EXEC = ../bin/BatailleNavale
CFLAGS = -Wall -I ../include
SRCS = $(OBJS:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	-rm -rf ./*.o
