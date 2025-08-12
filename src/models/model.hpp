#pragma once

#include "../views/boardView.hpp"
#include "entities/spike.hpp"
#include "entities/apple.hpp"
#include "entities/drawable.hpp"
#include "entities/snakeContainer.hpp"
#include "structs/boardDimensions.hpp"
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <mutex>
#include <unordered_set>

class Model {
public:
  Model(int height, int width, int numApples, int numSpikes)
      : board(height, width), 
        game_over(false),
        snake(5, 5),
        boardDimensions({height - 2, width - 2}){
    board.initialize();

    entities.insert(snake.peekFront());
    for(int i=0; i<numApples; i++) addApple();
    for(int i=0; i<numSpikes; i++) addSpike();
  }

  void processInput(chtype input) {
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

      if (entities.size() == (uint)(boardDimensions.width * boardDimensions.height) &&
          std::find_if(entities.begin(), entities.end(), [](auto e){return e->getIcon() == 'A';}) == entities.end()
        ) {
        game_over = true;
        game_won = true;
      } else {
        addApple();
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

  void lock() { boardLock.lock(); }

  void unlock() {boardLock.unlock(); };

private:
  const BoardView board;
  bool game_over;
  bool game_won;
  std::mutex boardLock;

  std::unordered_set<std::shared_ptr<Drawable>> entities;
  SnakeContainer snake;
  const BoardDimensions boardDimensions;

  void addApple(){
    auto pos = getRandomOpenPosition();
    entities.insert(std::make_shared<Apple>(pos.y, pos.x));
  }

  void addSpike(){
    auto pos = getRandomOpenPosition();
    entities.insert(std::make_shared<Spike>(pos.y, pos.x));
  }

  const Position getRandomOpenPosition() const {
    std::unordered_set<int> openPositions;
    for (int i = 0; i < boardDimensions.height * boardDimensions.width; i++) {
      openPositions.insert(i);
    }
    for (auto e : entities) {
      openPositions.erase(e->getX() + e->getY() * boardDimensions.width);
    }
    
    if(openPositions.size() == 0) {return {y:-1, x:-1};}

    auto it = openPositions.begin();
    std::advance(it, (rand() % openPositions.size()));

    return {y:(*it) / boardDimensions.width,  x: (*it) % boardDimensions.width};
  }
};
