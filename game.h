#include <stdlib.h>
#include "raylib.h"

#define BOARD_SIZE 15
#define TILE_SIZE 50
#define WINDOW_SIZE 750

enum {
  DIR_UP    = 0,
  DIR_DOWN  = 1,
  DIR_RIGHT = 2,
  DIR_LEFT  = 3
};

enum {
  TILE_BLANK = 0,
  TILE_HEAD  = 1,
  TILE_APPLE = 2,
  TILE_WALL  = 3,
  TILE_SNAKE = 4,
};

typedef struct node {
  int x;
  int y;
  struct node* next;
} node_t;

// board[y][x]
extern int board[BOARD_SIZE][BOARD_SIZE];
extern node_t* tail;
extern node_t* head;
extern int direction;
extern int frameCounter;
extern bool isGameOver;

void apple_spawn(void) {
  int newX = 0;
  int newY = 0;
  do {
    newX = GetRandomValue(1, BOARD_SIZE);
    newY = GetRandomValue(1, BOARD_SIZE);
  } while (board[newY][newX] != TILE_BLANK);

  board[newY][newX] = TILE_APPLE;
}

void snake_kill(void) {
  node_t* current = tail;
  while (current != NULL) {
    node_t* next = current->next;
    free(current);
    current = next;
  }
  head = NULL;
  tail = NULL;
}

void game_start(void) {
  // variables
  direction = DIR_LEFT;
  frameCounter = 0;
  isGameOver = false;

  // board
  for (int y = 0; y < BOARD_SIZE; ++y) {
    for (int x = 0; x < BOARD_SIZE; ++x) {
      if (board[y][x] != TILE_BLANK && board[y][x] != TILE_WALL) {
        board[y][x] = TILE_BLANK;
      }
    }
  }

  // walls
  for (int i = 0; i < BOARD_SIZE; ++i) {
    board[0][i] = TILE_WALL;
    board[BOARD_SIZE - 1][i] = TILE_WALL;
    board[i][0] = TILE_WALL;
    board[i][BOARD_SIZE - 1] = TILE_WALL;
  }

  // kill old snake
  snake_kill();

  // create new snake
  tail = malloc(sizeof(node_t));
  tail->x = 12;
  tail->y = 7;

  tail->next = malloc(sizeof(node_t));
  tail->next->x = 11;
  tail->next->y = 7;

  head = malloc(sizeof(node_t));
  head->x = 10;
  head->y = 7;

  tail->next->next = head;
  head->next = NULL;

  // apple
  apple_spawn();
}

void game_input(void) {
  if (IsKeyPressed(KEY_R)) {
    game_start();
  }
  if (IsKeyPressed(KEY_UP) && direction != DIR_DOWN) {
    direction = DIR_UP;
  }
  if (IsKeyPressed(KEY_DOWN) && direction != DIR_UP) {
    direction = DIR_DOWN;
  }
  if (IsKeyPressed(KEY_RIGHT) && direction != DIR_LEFT) {
    direction = DIR_RIGHT;
  }
  if (IsKeyPressed(KEY_LEFT) && direction != DIR_RIGHT) {
    direction = DIR_LEFT;
  }
}

void snake_process(void) {
  int dx = 0;
  int dy = 0;

  switch (direction) {
    case DIR_UP:    dy = -1; break;
    case DIR_DOWN:  dy =  1; break;
    case DIR_LEFT:  dx = -1; break;
    case DIR_RIGHT: dx =  1; break;
  }

  int nextX = head->x + dx;
  int nextY = head->y + dy;

  if (board[nextY][nextX] >= TILE_WALL) {
    isGameOver = true;
    return;
  }
  else if (board[nextY][nextX] == TILE_BLANK) {
    node_t* current = tail;
    board[tail->y][tail->x] = TILE_BLANK;

    while (current->next != NULL) {
      current->x = current->next->x;
      current->y = current->next->y;
      current = current->next;
    }
    head->x += dx;
    head->y += dy;
  }
  else if (board[nextY][nextX] == TILE_APPLE) {
    node_t* newNode = malloc(sizeof(node_t));
    head->next = newNode;
    head = newNode;
    newNode->next = NULL;
    newNode->x = nextX;
    newNode->y = nextY;
    apple_spawn();
  }
}

void snake_set(void) {
  // Updates the board data with the new snake positions
  // Inefficient, for sure, but this is a demo.
  node_t* current = tail;

  while (current->next != NULL) {
    board[current->y][current->x] = TILE_SNAKE;
    current = current->next;
  }
  board[head->y][head->x] = TILE_HEAD;
}

void game_update(void) {
  frameCounter++;
  if (frameCounter >= 10) {
    frameCounter = 0;
    snake_process();
    snake_set();
  }
}

void game_draw(void) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  for (int y = 0; y < BOARD_SIZE; ++y) {
    for (int x = 0; x < BOARD_SIZE; ++x) {
      Color col;
      switch (board[y][x]) {
        case TILE_BLANK:
          col = RAYWHITE;
          break;
        case TILE_WALL:
          col = GRAY;
          break;
        case TILE_SNAKE:
          col = DARKGREEN;
          break;
        case TILE_HEAD:
          col = GREEN;
          break;
        case TILE_APPLE:
          col = RED;
          break;
      }
      DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, col);
    }
  }
  EndDrawing();
}
