SRC_ALL := $(wildcard src/*.c)
SRC_MAIN := src/main.c
SRC_CORE := $(filter-out $(SRC_MAIN), $(SRC_ALL))

OBJ_MAIN := $(SRC_MAIN:.c=.o)
OBJ_CORE := $(SRC_CORE:.c=.o)

TARGET := emax-chess-zero
PERFT_SRC := tests/perft.c
PERFT_OUT := test-perft

CC = gcc
CFLAGS = -Wall -O3 -flto -Iinclude

$(TARGET): $(OBJ_CORE) $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(PERFT_OUT): $(PERFT_SRC) $(OBJ_CORE)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

run-perft: $(PERFT_OUT)
	./$(PERFT_OUT)

clean:
	rm -f src/*.o $(TARGET) $(PERFT_OUT)
