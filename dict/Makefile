CC = gcc

CCFLAGS = -I inc -O2 -Wall -Wextra

SRCS = main.c src/word.c src/dict.c

all: $(SRCS)
	 $(CC) $^ $(CCFLAGS) -o main.elf

elf: all

clean:
	rm -rf main.elf main.o
