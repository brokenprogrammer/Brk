# This is the initial makefile. There is some improvements to be made.
# TODO: Make this work on OSX and Linux as well.
# TODO: Look into what linker flags and compiler flags are necessary.

DISABLED_WARNINGS= -Wall
LDFLAGS=-pthread -lstdc++ #-lm
CFLAGS=-std=c++11
CC=clang++

debug:
	$(CC) src/main.cpp $(DISABLED_WARNINGS) $(CFLAGS) -g $(LDFLAGS) -o brk.exe

release:
	$(CC) src/main.cpp $(DISABLED_WARNINGS) $(CFLAGS) -O3 -march=native $(LDFLAGS) -o brk.exe
