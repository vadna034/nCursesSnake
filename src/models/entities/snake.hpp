#pragma once

#include "drawable.hpp"

#include <ncurses.h>

enum Direction {
  LEFT = KEY_LEFT, 
  RIGHT = KEY_RIGHT,
  UP = KEY_UP,
  DOWN = KEY_DOWN
};

class Snake : public Drawable{
public:
    Snake(int y, int x) : Drawable(y, x, 'S') {};
};
