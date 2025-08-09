#pragma once

#include <utility>
class Apple {
public: 
    Apple(std::pair<int,int> pos){
        this->pos = pos;
    }

private: 
    std::pair<int,int> pos;
};
