CC = gcc
CFLAGS = -Wall -Wpedantic -Wshadow
OBJECTS = encrypt.o aes.o

all:	encrypt

encrypt:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o encrypt

encrypt.o:	encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

aes.o:	aes.c
	$(CC) $(CFLAGS) -c aes.c

clean:
	rm -f $(OBJECTS) encrypt
