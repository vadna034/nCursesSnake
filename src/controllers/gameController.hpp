#pragma once

#include "../models/model.hpp"
#include <thread>

class GameController {
public:
  GameController(int boardRows, int boardCols, int numApples = 10, int numSpikes = 5) : model(boardRows, boardCols, numApples, numSpikes) {}

  void ProcessInput() {
    while (!model.isGameOver()) {
      auto ch = getch();
      model.lock();
      model.processInput(ch);
      model.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
  }

  void UpdateBoard() {
    while (!model.isGameOver()) {
      model.lock();
      model.updateState();
      model.redraw();
      model.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
  }

protected:
  Model model;
};
