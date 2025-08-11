
TARGET = nash
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

CFLAGS ?= -Wall -g -ansi -pedantic
LDFLAGS ?= 

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

