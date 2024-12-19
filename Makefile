# Détection de l'OS
OS := $(shell uname -s)

# Configuration par défaut
CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_ttf

# Spécifique à macOS
ifeq ($(OS), Darwin)
	CFLAGS += -I/opt/homebrew/include/
	LDFLAGS += -L/opt/homebrew/lib -framework Cocoa
endif

# Cibles principales
all: app

app: $(wildcard src/*.c)
	make -C libft re
	$(CC) $(wildcard src/*.c) libft.a -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f app

fclean: clean
	rm -f app

tclean:
	rm -f tests.out

re: fclean all

# Cible tests
tests: tclean
	$(CC) $(CFLAGS) tests/*.c src/player.c src/game.c src/app.c  $(LDFLAGS) -o tests.out
	./tests.out
