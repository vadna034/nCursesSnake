#pragma once

#include "snake.hpp"
#include "../structs/boardDimensions.hpp"
#include <memory>
#include <queue>

class SnakeContainer {
public:
    SnakeContainer(int y, int x) : dir(RIGHT){
        std::shared_ptr<Snake> s = std::make_shared<Snake>(y, x);
        body.push(s);
    }

    void push(int y, int x){
        std::shared_ptr<Snake> s = std::make_shared<Snake>(y, x);
        body.push(s);
    }

    void pop() {
        body.pop();
    }

    std::shared_ptr<Snake> peekFront() const{
        return body.front();
    }

    std::shared_ptr<Snake> peekBack() const {
        return body.back();
    }


    Position getNextPosition(const BoardDimensions& boardDimensions) const {
        const auto& [height, width] = boardDimensions;
        int xDiff = 0, yDiff = 0;

        if(dir == LEFT) xDiff = -1;
        if(dir == RIGHT) xDiff = 1;
        if(dir == UP) yDiff = -1;
        if(dir == DOWN) yDiff = 1;

        auto t = body.back();
    
        return {
            y: (body.back()->getY() + yDiff + height) % height, 
            x: (body.back()->getX() + xDiff + width) % width
        };
    }

    void processInput(chtype c) {
        switch(c){
            case LEFT:
                dir = LEFT;
                break;
            case RIGHT:
                dir = RIGHT;
                break;
            case UP:
                dir = UP;
                break;
            case DOWN:
                dir = DOWN;
                break;
            default: 
                break;
        }
    }

protected:
    Direction dir;
    std::queue<std::shared_ptr<Snake>> body;
};
