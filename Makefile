CC = clang
CFLAGS = -I/opt/homebrew/include/
LDFLAGS = -L/opt/homebrew/lib -lSDL2

all: app

app: main.c
	$(CC) main.c -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f app
