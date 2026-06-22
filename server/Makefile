CC = gcc

CFLAGS = -O2 -Wall -Wextra -g -I./include

SRC = $(shell find src -name "*.c")

TARGET = server.out

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lpq -lcrypto

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

re: clean all

.PHONY: all run clean re