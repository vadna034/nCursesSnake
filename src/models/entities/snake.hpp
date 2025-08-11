#pragma once

#include "drawable.hpp"
#include "../structs/boardDimensions.hpp"

#include <ncurses.h>

enum Direction {
  LEFT = KEY_LEFT, 
  RIGHT = KEY_RIGHT,
  UP = KEY_UP,
  DOWN = KEY_DOWN
};

class Snake : public Drawable {
public:
    Snake(int y, int x) : Drawable(y, x, 'S') {
        dir = RIGHT;
    };

    void move(const BoardDimensions& boardDimensions){
        switch(dir){
            case LEFT:
                updatePosition(-1, 0, boardDimensions);
                break;
            case RIGHT:
                updatePosition(1, 0, boardDimensions);
                break;
            case UP:
                updatePosition(0, -1, boardDimensions);
                break;
            case DOWN:
                updatePosition(0, 1, boardDimensions);
                break;
            default: 
                throw("NOT IMPLEMENTED");
        }
    }

    void processInput(chtype c) {
        switch(c){
            case LEFT:
                dir = LEFT;
                break;
            case RIGHT:
                dir = RIGHT;
                break;
            case UP:
                dir = UP;
                break;
            case DOWN:
                dir = DOWN;
                break;
            default: 
                break;
        }
    }

protected:
    Direction dir;

    void updatePosition(int xDiff, int yDiff, const BoardDimensions& boardDimensions){
        const auto& [height, width] = boardDimensions;

        x = (x + xDiff + width) % width;
        y = (y + yDiff + height) % height;
    }
};
