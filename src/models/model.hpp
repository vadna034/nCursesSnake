#pragma once

#include "../views/boardView.hpp"
#include "structs/boardDimensions.hpp"
#include "entities/apple.hpp"
#include "entities/snake.hpp"
#include <assert.h>
#include <memory>
#include <vector>

class Model {
public:
  Model(int height, int width) : board(height, width), game_over(false), boardDimensions({height-2, width-2}) {
    board.initialize();

    snake = std::make_shared<Snake>(5, 5);
    auto applePtr = std::make_shared<Apple>(10, 10);
    entities.assign({applePtr, snake});
  }

  void processInput() const {
    chtype input = getch();
    snake->processInput(input);
  }

  void updateState() const {
    snake->move(boardDimensions);

    board.clear();

    for (auto e : entities) {
      board.add(*e);
    }
  }

  void redraw() const { board.refresh(); }

  bool isGameOver() const { return game_over; }

private:
  const BoardView board;
  bool game_over;

  std::vector<std::shared_ptr<Drawable>> entities;
  std::shared_ptr<Snake> snake;
  const BoardDimensions boardDimensions;
};
