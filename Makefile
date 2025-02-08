# Détection de l'OS
OS := $(shell uname -s)

# Configuration par défaut
CC = gcc
CFLAGS = -Iinclude -I$(HOME)/libsdl2/include
LDFLAGS = -L$(HOME)/libsdl2/lib -Wl,-rpath=$(HOME)/libsdl2/lib -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

# Spécifique à macOS
ifeq ($(OS), Darwin)
	CFLAGS += -I/opt/homebrew/include/
	LDFLAGS += -L/opt/homebrew/lib -framework Cocoa
endif

# Spécifique à Linux
ifeq ($(OS), Linux)
	CFLAGS += -I/usr/include/
	LDFLAGS += -L/usr/lib/
endif

# Cibles principales
all: app

libft.a:
	make -C libft re

app: $(wildcard src/*.c) $(wildcard src/game/*.c) libft.a
	$(CC) $(wildcard src/*.c) $(wildcard src/game/*.c) libft.a -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f app
	make -C libft clean

fclean: clean
	rm -f app

tclean:
	rm -f tests.out

re: fclean all

# Cible tests
tests: tclean
	$(CC) $(CFLAGS) tests/*.c src/player.c src/game.c src/menu.c src/app.c src/asset.c libft.a $(LDFLAGS) -o tests.out
	./tests.out
