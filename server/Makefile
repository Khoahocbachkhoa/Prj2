CC = gcc
CFLAGS = -Wall -I./include

LIBS = -lpq

SRCS = src/main.c \
       $(wildcard src/core/*.c) \
       $(wildcard src/database/*.c) \
       $(wildcard src/protocol/*.c) \
       $(wildcard src/services/*.c) \
       $(wildcard src/transport/*.c)

TARGET = server.out

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)