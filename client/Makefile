CC = gcc

CFLAGS = -Wall -Wextra -I./include

TARGET = client.out

SRC = \
	src/main.c \
	src/core/app.c \
	src/core/state.c \
	src/parser/parser.c \
	src/command/dispatch.c \
	src/command/register.c \
	src/command/login.c \
	src/command/logout.c \
	src/command/exit.c \
	src/transport/transport.c \
	src/utils/security.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)