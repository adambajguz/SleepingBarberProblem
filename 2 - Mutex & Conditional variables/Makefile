CFLAGS = -g -O2 -std=gnu11
LIBS = -lm -pthread

OBJ =\
    barber.o \
	clients_queue.o \
	utils.o \
	main.o

all: main

clean:
		rm -f *.o main
.c.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) -o main