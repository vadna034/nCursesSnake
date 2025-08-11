#pragma once

#include <assert.h>
#include <memory>
#include <vector>
#include "../views/boardView.hpp"
#include "entities/snake.hpp"
#include "entities/apple.hpp"

class Model {
public:
    Model(int height, int width) : board(height, width), game_over(false) {
        board.initialize();

        snake = std::make_shared<Snake>(5,5);
        auto applePtr = std::make_shared<Apple>(10,10);
        entities.assign({applePtr, snake});
    }

    void processInput() const {
        chtype input = getch();
        snake->processInput(input);
    }

    void updateState() const
    {
        snake->move();

        board.clear();

        for(auto e : entities){
            board.add(*e);
        }
    }

    void redraw() const {
        board.refresh();
    }

    bool isGameOver() const {
        return game_over;
    }

private: 
    BoardView board;
    bool game_over;

    std::vector<std::shared_ptr<Drawable>> entities;
    std::shared_ptr<Snake> snake;
};
