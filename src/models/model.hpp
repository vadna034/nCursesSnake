#pragma once

#include <assert.h>
#include "../views/boardView.hpp"
#include "entities/snake.hpp"
#include "entities/apple.hpp"

class Model {
public:
    Model(int height, int width) : board(height, width), game_over(false) {
        board.initialize();
    }

    void processInput() const
    {
        chtype input = board.getInput();
    }

    void updateState() const
    {
        Snake s(5,5);
        Apple a(4,4);
        board.add(s);
        board.add(a);
    }

    void redraw() const {
        board.refresh();
    }

    bool isGameOver() const {
        return game_over;
    }

private: 
    BoardView board;
    bool game_over;
};
