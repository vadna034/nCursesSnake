#pragma once

#include <ncurses.h>

class Drawable {
  public: 
    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    chtype getIcon(){
        return icon;
    }

  protected: 
    Drawable(int y, int x, chtype ch){
        this->y = y;
        this->x = x;
        this->icon = ch;
    }

    int y, x;
    chtype icon;
};
