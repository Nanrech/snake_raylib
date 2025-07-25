#include "game.h"


int board[BOARD_SIZE][BOARD_SIZE] = {TILE_BLANK};
node_t* tail = NULL;
node_t* head = NULL;
int direction = DIR_LEFT;
int frameCounter = 0;
bool isGameOver = false;

int main(void) {
  InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Shnake");
  SetTargetFPS(60);

  game_start();

  while (!WindowShouldClose()) {
    game_input();
    if (!isGameOver) {
      game_update();
    }
    game_draw();
  }

  snake_kill();
  CloseWindow();
  return 0;
}
