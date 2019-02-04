CC=gcc

CFLAGS= -std=c11 -Wall -Wextra -Werror -Wno-unused-parameter `pkg-config --cflags gtk+-3.0`
# ogolne flagi kompilacji dla modulow

LDFLAGS= `pkg-config --libs gtk+-3.0`
# ogolne flagi konsolidacji programu

DEPS = move.h base.h coordinates.h communication.h fifo.h definitions.h
NAME = kropki

$(NAME): main.c coordinates.o move.o communication.o base.o fifo.o $(DEPS)
	$(CC) $(CFLAGS) main.c coordinates.o move.o communication.o base.o fifo.o -o $(NAME) $(LDFLAGS)

coordinates.o: coordinates.c $(DEPS)
	$(CC) -c $(CFLAGS) coordinates.c -o coordinates.o $(LDFLAGS)

move.o: move.c base.o $(DEPS)
	$(CC) -c $(CFLAGS) move.c base.o -o move.o

base.o: base.c $(DEPS)
	$(CC) -c $(CFLAGS) base.c -o base.o

communication.o: communication.c fifo.o $(DEPS)
	$(CC) -c $(CFLAGS) communication.c fifo.o -o communication.o $(LDFLAGS)

fifo.o: fifo.c $(DEPS)
	$(CC) -c $(CFLAGS) fifo.c -o fifo.o $(LDFLAGS) 
