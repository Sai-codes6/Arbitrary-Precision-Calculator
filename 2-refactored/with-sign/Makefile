# ============================================================
#  Makefile - Arbitrary Precision Calculator
#  I keep the build deliberately small: one engine translation
#  unit (bignum.c) plus the CLI driver (main.c).
# ============================================================

# compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2
DEBUGFLAGS := -Wall -Wextra -std=c11 -g -O0

# final binary name
TARGET  := apc

# every source file in the project
SRCS    := main.c bignum.c
# object files derived from the sources
OBJS    := $(SRCS:.c=.o)
# the public header that every source depends on
HEADERS := bignum.h

# ------------------------------------------------------------
# default target: build the calculator
# ------------------------------------------------------------
all: $(TARGET)

# link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# compile each .c into its .o, rebuilding if the header changes
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------------
# debug build: no optimisation, symbols on, ready for gdb/valgrind
# ------------------------------------------------------------
debug: CFLAGS := $(DEBUGFLAGS)
debug: clean $(TARGET)

# ------------------------------------------------------------
# run a quick valgrind pass over a representative operation
# ------------------------------------------------------------
memcheck: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) 12345678901234567890 x 98765

# ------------------------------------------------------------
# remove every build artifact
# ------------------------------------------------------------
clean:
	rm -f $(OBJS) $(TARGET)

# these targets are not real files
.PHONY: all debug memcheck clean
