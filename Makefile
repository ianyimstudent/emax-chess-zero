CC = gcc
CFLAGS = -Wall -O3 -flto -march=native -Iinclude
SRC = src/main.c src/board.c src/move.c
OBJ = $(SRC:.c=.o)
TARGET = emax-chess-zero

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
