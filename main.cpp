#include "src/controllers/gameController.hpp"

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
    nodelay(stdscr, TRUE);
  srand(time(NULL));
  curs_set(0);

  GameController controller(BOARD_ROWS, BOARD_COLS);

  std::thread inputThread(&GameController::ProcessInput, &controller);
  std::thread updateThread(&GameController::UpdateBoard, &controller);
  inputThread.join();
  updateThread.join();

  getch();
  endwin();

  return 0;
}
