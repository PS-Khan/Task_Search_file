# Makefile for building the static library and test application

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

# Targets
all: libfile_search_lib.a test_app

# Rule to build the static library
libfile_search_lib.a: file_search_lib.o
		ar rcs $@ $<

# Rule to build the test application
test_app: main.o libfile_search_lib.a
		$(CC) $(CFLAGS) -o $@ main.o -L. -lfile_search_lib -pthread

# Clean rule to remove object files and executables
clean:
		rm -f *.o libfile_search_lib.a test_app