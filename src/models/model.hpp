#pragma once

#include "../views/boardView.hpp"
#include "entities/apple.hpp"
#include "entities/drawable.hpp"
#include "entities/snake.hpp"
#include "structs/boardDimensions.hpp"
#include <algorithm>
#include <assert.h>
#include <memory>
#include <unordered_set>
#include <vector>
#include <random>

class Model {
public:
  Model(int height, int width)
      : board(height, width), game_over(false),
        boardDimensions({height - 2, width - 2}) {
    board.initialize();

    snake = std::make_shared<Snake>(5, 5);
    auto applePtr = std::make_shared<Apple>(10, 10);
    entities.insert({applePtr, snake});
  }

  void processInput() const {
    chtype input = getch();
    snake->processInput(input);
  }

  void updateState() {
    snake->move(boardDimensions);
    handleCollisions();

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

  std::unordered_set<std::shared_ptr<Drawable>> entities;
  std::shared_ptr<Snake> snake;
  const BoardDimensions boardDimensions;

  void handleCollisions() {
    std::vector<std::shared_ptr<Drawable>> collidedVals;
    std::copy_if(entities.begin(), entities.end(),
                 std::back_inserter(collidedVals), [&](auto v) {
                   return v != snake &&
                          Drawable::areDrawablesCollided(*v, *snake);
                 });

    for (auto v : collidedVals) {
      entities.erase(v);
      auto [x, y] = getOpenPosition();
      auto newApple = std::make_shared<Apple>(x, y);
      entities.insert(newApple);
    }
  }

  std::pair<int,int> getOpenPosition() {
    const auto& [height, width] = boardDimensions;
    int count = height * width; 
    std::vector<bool> isPopulated(height * width, false);

    for (auto e : entities) {
        int idx = e->getY() * boardDimensions.width + e->getX();
        count += isPopulated[idx] == false;
        isPopulated[idx] = true;
    }

    int countFoundOpen = 0;
    int idx = rand() % count;

    for(int i=0; i<isPopulated.size(); i++){
        countFoundOpen += !isPopulated[i];
        if(countFoundOpen > idx) return {i / width, i % width};
    }

    return {-1,-1};
  }
};
