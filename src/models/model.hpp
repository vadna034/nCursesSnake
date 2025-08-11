#pragma once

#include "../views/boardView.hpp"
#include "entities/apple.hpp"
#include "entities/drawable.hpp"
#include "entities/snakeContainer.hpp"
#include "structs/boardDimensions.hpp"
#include <assert.h>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <unordered_set>

class Model {
public:
  Model(int height, int width)
      : board(height, width), 
        game_over(false),
        snake(5, 5),
        boardDimensions({height - 2, width - 2}){
    board.initialize();

    entities.insert(snake.peekFront());
    auto applePtr = std::make_shared<Apple>(10, 10);
    entities.insert({applePtr});
  }

  void processInput() {
    chtype input = getch();
    snake.processInput(input);
  }

  void updateState() {
    auto nextPos = snake.getNextPosition(boardDimensions);

    std::shared_ptr<Drawable> collidedPiece = nullptr;

    for (auto e : entities) {
      if (e->getX() == nextPos.x && e->getY() == nextPos.y)
        collidedPiece = e;
    }

    snake.push(nextPos.y, nextPos.x);
    entities.insert(snake.peekBack());

    if (collidedPiece == nullptr) {
      entities.erase(snake.peekFront());
      snake.pop();
    } else if (collidedPiece->getIcon() == 'A') {
      entities.erase(collidedPiece);

      if (entities.size() == (uint)(boardDimensions.width * boardDimensions.height)) {
        game_over = true;
        game_won = true;
      } else {
        auto pos = getRandomOpenPosition();
        entities.insert(std::make_shared<Apple>(pos.y, pos.x));
      }
    } else {
      game_over = true;
    }

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
  bool game_won;

  std::unordered_set<std::shared_ptr<Drawable>> entities;
  SnakeContainer snake;
  const BoardDimensions boardDimensions;

  Position getRandomOpenPosition() {
    std::unordered_set<int> openPositions;
    for (int i = 0; i < boardDimensions.height * boardDimensions.width; i++) {
      openPositions.insert(i);
    }
    for (auto e : entities) {
      openPositions.erase(e->getX() + e->getY() * boardDimensions.width);
    }
    auto it = openPositions.begin();
    std::advance(it, (rand() % openPositions.size()));

    return {y:(*it) / boardDimensions.width,  x: (*it) % boardDimensions.width};
  }
};
