#pragma once

#include "../structs/boardDimensions.hpp"
#include "snake.hpp"
#include <memory>
#include <queue>
#include <unordered_map>

enum Direction {
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3,
};

const std::unordered_map<chtype, Direction> DIRECTION_MAP{
    {KEY_LEFT, LEFT}, {KEY_RIGHT, RIGHT}, {KEY_UP, UP}, {KEY_DOWN, DOWN}};

class SnakeContainer {
public:
  SnakeContainer(int y, int x) : dir(RIGHT) {
    std::shared_ptr<Snake> s = std::make_shared<Snake>(y, x);
    body.push(s);
  }

  void push(int y, int x) {
    prevDir = dir;
    std::shared_ptr<Snake> s = std::make_shared<Snake>(y, x);
    body.push(s);
  }

  void pop() { body.pop(); }

  std::shared_ptr<Snake> peekFront() const { return body.front(); }

  std::shared_ptr<Snake> peekBack() const { return body.back(); }

  Position getNextPosition(const BoardDimensions &boardDimensions) const {
    const auto &[height, width] = boardDimensions;
    int xDiff = 0, yDiff = 0;

    if (dir == LEFT)
      xDiff = -1;
    if (dir == RIGHT)
      xDiff = 1;
    if (dir == UP)
      yDiff = -1;
    if (dir == DOWN)
      yDiff = 1;

    auto t = body.back();

    return {
      y : (body.back()->getY() + yDiff + height) % height,
      x : (body.back()->getX() + xDiff + width) % width
    };
  }

  void processInput(chtype c) {
    if(!DIRECTION_MAP.count(c)) return;

    Direction newDir = DIRECTION_MAP.at(c);
    if ((newDir + 2) % DIRECTION_MAP.size() != prevDir) {
      dir = DIRECTION_MAP.at(c);
    }
  }

protected:
  Direction dir;
  Direction prevDir;
  std::queue<std::shared_ptr<Snake>> body;
};
