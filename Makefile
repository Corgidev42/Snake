CC = gcc
CFLAGS = -I/opt/homebrew/include/ -Iinclude
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2main -framework Cocoa

all: app

app: main.c
	$(CC) main.c -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f app

fclean: clean
	rm -f app

tclean:
	rm -f tests.out

re: fclean all

tests: tclean
	gcc -Iinclude tests/*.c src/player.c -o tests.out
	./tests.out

