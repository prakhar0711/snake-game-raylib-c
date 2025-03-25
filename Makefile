
CC = cc
CFLAGS = -Wall -Wextra -Wpedantic
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -pg
TARGET = main
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
