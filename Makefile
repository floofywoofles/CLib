CC=clang
CFLAGS=-Wall -Wextra -pedantic -O0

all: dirs build

dirs:
	mkdir -p bin

build:
	$(CC) $(CFLAGS) -g ./src/*.c -o bin/a.out