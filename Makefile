CC=clang
CFLAGS=-Wall -Wextra -pedantic -O0

all: dirs build

dirs:
	mkdir -p bin

build:
	$(CC) $(CFLAGS) -I ./include ./src/*.c -o bin/a.out