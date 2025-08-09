#pragma once

#include "IEntity.hpp"
#include <ncurses.h>
#include <queue>
#include <utility>

enum Direction { LEFT = KEY_LEFT, RIGHT = KEY_RIGHT , UP = KEY_UP, DOWN = KEY_DOWN };

class SnakeEntity : IEntity {
public:
    SnakeEntity(std::pair<int,int> startPos){
        int i = startPos.first;
        int j = startPos.second;

        for(int k=0; k<2; k++){
            positions.push({i, j+k});
        }

        direction = RIGHT;
    }

    void pop_back(){
        positions.pop();
    }

    void push_next(){
        auto next = getNextPosition();
        positions.push(next); 
    }

    void sendDirectionChar(char c){
        switch (c) {
            case LEFT: 
            case RIGHT:
            case UP:
            case DOWN:
                direction = (Direction)c;
                break;
        }
    }

private: 
    std::queue<std::pair<int,int>> positions;
    Direction direction;

    std::pair<int,int> getNextPosition(){
        auto front = positions.front();

        switch(direction){
            case LEFT: 
                front.second--;
                break;
            case RIGHT:
                front.second++;
                break;
            case UP:
                front.first--;
                break;
            case DOWN:
                front.first++;
                break;
            default: 
                throw("Not implemented");
        }

        return front;
    }
};
