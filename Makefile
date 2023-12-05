CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = source
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRCS:.c=.o)

all: Radial

Radial: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lcurl -lcjson

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) Radial