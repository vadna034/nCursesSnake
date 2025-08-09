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

    void updateBoard(){
        model -> updateBoard();
    }

private: 
    Model* model;
};
