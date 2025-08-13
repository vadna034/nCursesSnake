#pragma once
#include <assert.h>
#include <ncurses.h>
#include <string>

#include "../models/entities/drawable.hpp"

class BoardView {
public:
  BoardView(int height, int width) {
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    board_win =
        newwin(height, width, yMax / 2 - height / 2, xMax / 2 - width / 2);
    wtimeout(board_win, 100);
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

  void addGameOverScreen(int score) const {
    int xMax, yMax;
    getmaxyx(board_win, yMax, xMax);

    wclear(board_win);
    addBorder();
    std::string gameOverMessage = "Game over: final score " + std::to_string(score);
    mvwprintw(board_win, yMax/2, xMax/2 - (gameOverMessage.length() / 2), "%s", gameOverMessage.c_str());
  }

private:
  WINDOW *board_win;

  void addBorder() const { box(board_win, 0, 0); }

  void addAt(int i, int j, chtype c) const {
    mvwaddch(board_win, i + 1, j + 1, c);
  }
};
