#pragma once

#include "drawable.hpp"

class Snake : public Drawable {
public:
    Snake(int y, int x) : Drawable(y, x, 'S') {};
};
