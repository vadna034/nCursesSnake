#pragma once

#include "drawable.hpp"

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

    void move(){
        switch(dir){
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
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
        }
    }

protected:
    Direction dir;
};
