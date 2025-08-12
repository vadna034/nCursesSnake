#include "src/controllers/gameController.hpp"

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define BOARD_DIM 4
#define BOARD_ROWS (BOARD_DIM * 5 - 2)
#define BOARD_COLS (BOARD_DIM * 11 - 2)
#define DEFAULT_APPLE_COUNT 10
#define DEFAULT_SPIKE_COUNT 0

void unpackCommandLineArgs(int argc, char** argv, int& numApples, int& numSpikes){
  numApples = argc >= 2 ? strtol(argv[1], nullptr, 0) : DEFAULT_APPLE_COUNT;
  numSpikes = argc >= 3 ? strtol(argv[2], nullptr, 0) : DEFAULT_SPIKE_COUNT;
}

int main(int argc, char** argv) {
  initscr();
  refresh();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  srand(time(NULL));
  curs_set(0);

  int numApples, numSpikes;
  unpackCommandLineArgs(argc, argv, numApples, numSpikes);
  GameController controller(BOARD_ROWS, BOARD_COLS, numApples, numSpikes);

  std::thread inputThread(&GameController::ProcessInput, &controller);
  std::thread updateThread(&GameController::UpdateBoard, &controller);
  inputThread.join();
  updateThread.join();

  getch();
  endwin();

  return 0;
}

