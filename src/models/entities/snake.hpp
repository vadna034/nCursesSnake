#pragma once

#include "drawable.hpp"

#include <ncurses.h>

class Snake : public Drawable{
public:
    Snake(int y, int x) : Drawable(y, x, 'S') {};
};
