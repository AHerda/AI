SOURCES = $(wildcard *.c)
BINARY = $(patsubst %.c, %, $(SOURCES))

FLAGS = -W -pedantic -std=c17 -O3
.PHONY = all clean

all: $(BINARY) bot

$(BINARY): %: %.c
	$(CC) $(FLAGS) $^ -o $@
	strip $@

bot: game_bot.cpp
	g++ -W -pedantic -O3 -o game_bot game_bot.cpp

clean:
	rm -f $(BINARY)

