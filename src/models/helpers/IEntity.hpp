#pragma once

#include <utility>
#include <vector>

class IEntity {
    virtual std::vector<std::pair<int,int>> getPositions();
    virtual char getIdentifier();
};
