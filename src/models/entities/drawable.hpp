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

    static bool areDrawablesCollided(const Drawable& v1, const Drawable& v2){
        return v1.x == v2.x && v1.y == v2.y;
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
