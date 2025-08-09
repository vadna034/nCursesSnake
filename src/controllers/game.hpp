#pragma once

#include "../models/model.hpp"

class Game {
public: 
    Game(Model& model) {
        this->model = &model;
    }

    void inputChar(char c){
        model -> sendChar(c);
    }

private: 
    Model* model;
};
