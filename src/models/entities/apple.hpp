#pragma once
#include "drawable.hpp"
#include <ncurses.h>


class Apple : public Drawable {
public: 
    Apple(int y, int x) : Drawable(y, x, 'A') {};
};
