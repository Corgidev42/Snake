CC = gcc
CFLAGS = 
LDFLAGS = -I/usr/lib/include -lSDL2 -lSDL2main

all: app

app: main.c
	$(CC) main.c -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f app

fclean: clean
	rm -f app

re: fclean all
