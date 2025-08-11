#include "src/models/model.hpp"
#include "src/views/boardView.hpp"

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define BOARD_DIM 4
#define BOARD_ROWS (BOARD_DIM * 5 - 2)
#define BOARD_COLS (BOARD_DIM * 11 - 2)

int main() {
  initscr();
  refresh();
  noecho();
  keypad(stdscr, TRUE);
  srand(time(NULL));
  curs_set(0);

  Model game(BOARD_ROWS, BOARD_COLS);

  while (!game.isGameOver()) {
    game.processInput();
    game.updateState();
    game.redraw();
  }

  getch();
  endwin();

  return 0;
}
