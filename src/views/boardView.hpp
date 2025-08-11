#pragma once
#include <assert.h>
#include <ncurses.h>

#include "../models/entities/drawable.hpp"

class BoardView {
public:
  BoardView(int height, int width) {
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    board_win =
        newwin(height, width, yMax / 2 - height / 2, xMax / 2 - width / 2);
  }

  void initialize() const {
    clear();
    refresh();
  }

  void refresh() const { wrefresh(board_win); }

  void add(Drawable drawable) const {
    addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
  }

  void clear() const {
    wclear(board_win);
    addBorder();
  }

private:
  WINDOW *board_win;

  void addBorder() const { box(board_win, 0, 0); }

  void addAt(int i, int j, chtype c) const {
    mvwaddch(board_win, i + 1, j + 1, c);
  }
};
