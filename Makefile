# Détection de l'OS
OS := $(shell uname -s)

# Configuration par défaut
CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -lSDL2 -lSDL2main

# Spécifique à macOS
ifeq ($(OS), Darwin)
    CFLAGS += -I/opt/homebrew/include/ -Iinclude
    LDFLAGS += -L/opt/homebrew/lib -framework Cocoa
endif

# Spécifique à Linux
ifeq ($(OS), Linux)
    CFLAGS += -Iinclude
    LDFLAGS +=
endif

# Cibles principales
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

# Cible tests
tests: tclean
	$(CC) $(CFLAGS) $(LDFLAGS) tests/*.c src/player.c -o tests.out
	./tests.out
