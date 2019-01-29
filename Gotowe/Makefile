CC=gcc

CFLAGS= -std=c11 -Wall -Wextra -Werror -Wno-unused-parameter `pkg-config --cflags gtk+-3.0`
# ogolne flagi kompilacji dla modulow

LDFLAGS= `pkg-config --libs gtk+-3.0`
# ogolne flagi konsolidacji programu

DEPS = base.h coordinates.h move.h definitions.h
NAME = kropki

$(NAME): main.c base.o coordinates.o move.o $(DEPS)
	$(CC) $(CFLAGS) main.c base.o coordinates.o move.o -o $(NAME) $(LDFLAGS)

move.o: move.c base.o $(DEPS)
	$(CC) -c $(CFLAGS) move.c base.o -o move.o

base.o: base.c $(DEPS)
	$(CC) -c $(CFLAGS) base.c -o base.o

coordinates.o: coordinates.c $(DEPS)
	$(CC) -c $(CFLAGS) coordinates.c -o coordinates.o $(LDFLAGS)
