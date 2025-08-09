#pragma once

#include "../models/model.hpp"

class GameController {
public: 
    GameController(Model& model) {
        this->model = &model;
    }

    void inputChar(char c){
        model -> sendDirectionChar(c);
    }

private: 
    Model* model;
};
