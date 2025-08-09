#pragma once

#include "helpers/snake.hpp"
#include "helpers/apple.hpp"
#include <vector>
#include <assert.h>

class Model {
public:
    Model(int height, int width)
        : snake({height/4, width/4}),
          apple({height*3/4, height*3/4}),
          boardState()
    {
        assert(height > 5 && width > 5);
    }

    void sendChar(char c) {
        snake.sendChar(c); 
    }

private: 
    Snake snake;
    Apple apple;
    std::vector<std::vector<char>> boardState;
};
