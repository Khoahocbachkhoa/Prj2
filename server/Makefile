CC = gcc
CFLAGS = -Wall -I./include

LIBS = -lpq

SRCS = $(shell find src -name "*.c") 

OBJ = $(SRCS:.c=.o)

TARGET = server.out

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)