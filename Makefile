CC = gcc
SRC = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
LSRC = $(wildcard include/*/*.c)
INCLUDES = include
LIBS = -lraylib -lgdi32 -lwinmm -lbox2d -lm
TARGET = .exe

all:
	@echo "Searching for errors..."
	@$(CC) $(LSRC) $(SRC) -o o$(TARGET) -I $(INCLUDES) -L lib $(LIBS)
	@echo "o$(TARGET) created"

clean:
	@rm -f *$(TARGET)
	@echo "All output files has been cleared"

debug:
	@echo "Debug mode:"
	@echo "Searching for errors..."
	@$(CC) -DDEBUG $(SRC) -o d$(TARGET) -I $(INCLUDES) -L lib $(LIBS) 
	@echo "d$(TARGET) created"
