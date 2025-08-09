#pragma once

#include "helpers/snakeEntity.hpp"
#include <vector>
#include <assert.h>

class Model {
public:
    Model(int height, int width)
        : snake({height/4, width/4}),
          boardState(std::vector(height, std::vector(width, ' ')))
    {
        assert(height > 5 && width > 5);
    }

    void sendDirectionChar(char c) {
        snake.sendDirectionChar(c); 
    }

    void updateBoard(){
        snake.push_next();
        snake.pop_back();
    }

private: 
    SnakeEntity snake;
    std::vector<std::vector<char>> boardState;
};
