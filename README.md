Demo of the game snake using raylib.
<img width="752" height="788" alt="SNAKE" src="https://github.com/user-attachments/assets/45655424-64f3-418d-9453-8efaad05fe3f" />

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
