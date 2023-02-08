CC  = gcc
CXX = g++

CXXFLAGS = -I inc -Wall -Wextra
DBGFLAGS = -fsanitize=address -ggdb3

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

depend: $(SRCS)
	$(CXX) -MM $(SRCS) -o depends

all: main.o
	 $(CXX) $^ $(CXXFLAGS) -o main.elf -O2

elf: all

dbg: $(SRCS)
	 $(CXX) $^ $(DBGFLAGS) $(CXXFLAGS) -o main.elf -O0

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@ -c

release: $(SRCS)
	$(CXX) $^ $(CXXFLAGS) -o main_release.elf -O2 -s

-include depends

clean:
	- rm -rf main.elf
	- rm -rf *.o *.elf
