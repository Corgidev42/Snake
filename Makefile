CC = gcc
CFLAGS = -I/opt/homebrew/include/
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2main -framework Cocoa

all: app

app: main.c
	$(CC) main.c -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f app

fclean: clean
	rm -f app

re: fclean all
