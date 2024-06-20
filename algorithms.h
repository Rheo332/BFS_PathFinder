#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "config.h"
#include "tile.h"

class Algorithms
{
public:
    Algorithms();

    void startSearching(Tile *tiles[Config::fieldSize][Config::fieldSize]);

private:
    bool isValid(int x, int y, Tile *tiles[Config::fieldSize][Config::fieldSize]);
    void delay(int ms);
    void markPath(std::vector<std::vector<std::pair<int, int>>> &parent,
                  Tile *tiles[Config::fieldSize][Config::fieldSize],
                  int endX,
                  int endY);
};

#endif // ALGORITHMS_H
