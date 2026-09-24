CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -Iinclude
LDFLAGS = -lm

TARGET  = rpn

SRC     = main.c \
          src/cpargs.c \
          src/getop.c \
          src/stack.c

OBJ     = $(SRC:.c=.o)

.PHONY: all clean re

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all
