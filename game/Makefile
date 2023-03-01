CC  = gcc
CXX = g++

CXXFLAGS = -I inc -Wall -Wextra
DBGFLAGS = -fsanitize=address -ggdb3

SRCS = main.cpp src/*.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(SRCS)
	 $(CXX) $^ $(CXXFLAGS) -o main.elf

elf: all

dbg: $(SRCS)
	 $(CXX) $^ $(DBGFLAGS) $(CXXFLAGS) -o main.elf -O0

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@ -c

release: $(SRCS)
	$(CXX) $^ $(CXXFLAGS) -o main_release.elf -O2 -s

-include depends

depend: $(SRCS)
	$(CXX) -MM $(SRCS) -o depends

clean:
	- rm -rf *.o *.elf
