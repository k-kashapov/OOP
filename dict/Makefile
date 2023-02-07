CC = gcc

CCFLAGS = -I inc -O2 -Wall -Wextra

DBGFLAGS = -fsanitize=address -ggdb3

SRCS = main.c src/*

all: $(SRCS)
	 $(CC) $^ $(CCFLAGS) -o main.elf

elf: all

dbg: $(SRCS)
	 $(CC) $^ $(DBGFLAGS) $(CCFLAGS) -o main.elf	

clean:
	rm -rf main.elf main.o
