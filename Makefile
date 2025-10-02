CC = clang

CFLAGS = -Wall -Iinclude

LDFLAGS = -lraylib

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = flappy_game
EXEC = out/$(TARGET)

BUILD = $(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(BUILD)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(OBJ)
	$(BUILD) && $(EXEC)

runc: $(OBJ)
	$(BUILD) && $(EXEC) && make clean

clean:
	rm -f $(OBJ) $(EXEC)