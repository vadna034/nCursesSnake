# Define variables
CC = gcc
CFLAGS = -Wall -g -lncurses
TARGET = main
SOURCES = main.cpp 

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SOURCES:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(SOURCES:.c=.o)
