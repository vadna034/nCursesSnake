#pragma once

#include "drawable.hpp"
#include <ncurses.h>

class Spike : public Drawable {
public: 
    Spike(int y, int x) : Drawable(y, x, 'X') {};
};
