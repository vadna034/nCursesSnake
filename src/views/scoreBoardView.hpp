#pragma once

#include <ncurses.h>
class ScoreBoardView {
    WINDOW *score_win;
    int width;

public:
    ScoreBoardView(int height, int width){
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        score_win = newwin(1, width, yMax/2 + height/2,  xMax/2 - width / 2);
        this->width = width;
    }

    void initialize(int initial_score) const
    {
        clear();
        mvwprintw(score_win, 0, 0, "Score: ");
        updateScore(initial_score);
        refresh();
    }

    void updateScore(int score) const {
        mvwprintw(score_win, 0, width - 11, "%11d", score);
    }

    void clear() const
    {
        wclear(score_win);
    }

    void refresh() const {
        wrefresh(score_win);
    }
};
