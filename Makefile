# Compiler and flags
CC = gcc
CFLAGS = -Wall -I.

# Source files and output
SOURCES = main.c musicdb.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = musicdb_report

# Default rule
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)