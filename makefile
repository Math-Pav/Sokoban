CC = gcc
CFLAGS = -Wall -g
OBJ = src/main.o src/game.o
TARGET = sokoban

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

src/main.o: src/main.c src/header.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/game.o: src/game.c src/header.h
	$(CC) $(CFLAGS) -c src/game.c -o src/game.o

run: $(TARGET)
	./$(TARGET)
	
clean:
	rm -f src/*.o $(TARGET)
