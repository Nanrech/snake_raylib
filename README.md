Demo of the game snake using raylib.

Makefile:
```
# Compiler and flags
CC = gcc
CFLAGS = -I[YOUR RAYLIB PATH HERE]
LDFLAGS = -L[YOUR RAYLIB PATH HERE] -lraylib -lopengl32 -lgdi32 -lwinmm

# Source and output
SRC = main.c
OUT = snake.exe

# Build target
all:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)
 ```
