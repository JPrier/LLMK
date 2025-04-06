# Unity unit test framework Makefile

# Paths
UNITY_PATH = unity
SRC_PATH = ../src
INC_PATH = ../inc
TEST_PATH = .

# Tools
CC = gcc
MKDIR = mkdir -p
RM = rm -f

# Flags
CFLAGS = -Wall -Wextra -I$(INC_PATH) -I$(UNITY_PATH) -DTEST

# Source files
UNITY_SRC = $(UNITY_PATH)/unity.c
TEST_SRC = $(wildcard test_*.c)

# Object files
UNITY_OBJ = $(UNITY_SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Test executables
TEST_BINS = $(TEST_SRC:.c=.bin)

.PHONY: all clean test

all: $(TEST_BINS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.bin: %.o $(UNITY_OBJ)
	$(CC) $^ -o $@

test: all
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

clean:
	$(RM) $(UNITY_OBJ) $(TEST_OBJ) $(TEST_BINS)
