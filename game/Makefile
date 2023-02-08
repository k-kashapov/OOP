CC  = gcc
CXX = g++

CXXFLAGS = -I inc -Wall -Wextra
DBGFLAGS = -fsanitize=address -ggdb3

SRCS = main.cpp src/*.cpp

all: $(SRCS)
	 $(CXX) $^ $(CXXFLAGS) -o main.elf -O2

elf: all

release: $(SRCS)
	$(CXX) $^ $(CXXFLAGS) -o main_release.elf -O2 -s

dbg: $(SRCS)
	 $(CXX) $^ $(DBGFLAGS) $(CXXFLAGS) -o main.elf -O0

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) $(DBGFLAGS) -o $@

clean:
	rm -rf main.elf main.o
