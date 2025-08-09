#pragma once
#include <ncurses.h>

class Board {
public:
  Board(int height, int width) : height(height), width(width) {
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    board_win =
        newwin(height, width, yMax / 2 - height / 2, xMax / 2 - width / 2);
    box(board_win, 0, 0);
    wrefresh(board_win);
  }

private:
  WINDOW *board_win;
  int height, width;
};
