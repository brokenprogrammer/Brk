# This is the initial makefile. There is some improvements to be made.
# TODO: Make this work on OSX and Linux as well.
# TODO: Look into what linker flags and compiler flags are necessary.

DISABLED_WARNINGS= -Wall
LDFLAGS=-pthread -lstdc++ #-lm
CFLAGS=-std=c++14
LLVMFLAGS=-IC:\msys32\mingw64/include -march=x86-64 -mtune=generic -O2 -pipe -D_GNU_SOURCE -Wa,-mbig-obj -Werror=date-time -std=gnu++11 -Wall -W -Wno-unused-parameter -Wwrite-strings -Wcast-qual -Wno-missing-field-initializers -pedantic -Wno-long-long -Wno-maybe-uninitialized -Wdelete-non-virtual-dtor -Wno-comment  -O2 -DNDEBUG  -fno-exceptions -fno-rtti -DLLVM_BUILD_GLOBAL_ISEL -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -LC:\msys32\mingw64/lib -lLLVM.dll
CC=clang++

debug:
	$(CC) $(llvm-config --cxxflags) src/main.cpp src/globals.cpp src/lexer.cpp src/parser.cpp src/expression.cpp $(LLVMFLAGS) $(DISABLED_WARNINGS) $(CFLAGS) -g $(LDFLAGS) -o brk.exe

release:
	$(CC) $(llvm-config --cxxflags) src/main.cpp $(DISABLED_WARNINGS) $(CFLAGS) -O3 -march=native $(LDFLAGS) -o brk.exe
