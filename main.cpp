#include "src/views/boardView.hpp"

#include <ncurses.h>

#define BOARD_DIM 4
#define BOARD_ROWS (BOARD_DIM * 5)
#define BOARD_COLS (BOARD_DIM * 11)

int main() {
  initscr();
  refresh();

  BoardView board(BOARD_ROWS, BOARD_COLS);

  getch();
  endwin();

  return 0;
}
