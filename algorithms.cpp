#include "algorithms.h"

#include <QApplication>
#include <QThread>
#include <queue>
#include <vector>

Algorithms::Algorithms() {}

void Algorithms::startSearching(Tile *tiles[Config::fieldSize][Config::fieldSize])
{
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    int startX = 1, startY = 1;

    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    tiles[startX][startY]->setColor(Tile::Visited);

    std::vector<std::vector<std::pair<int, int>>>
        parent(Config::fieldSize, std::vector<std::pair<int, int>>(Config::fieldSize, {-1, -1}));

    parent[startX][startY] = {startX, startY};

    bool found = false;
    int endX = -1, endY = -1;

    while (!q.empty() && !found) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY, tiles)) {
                parent[newX][newY] = {x, y};
                if (tiles[newX][newY]->getColor() == Tile::End) {
                    found = true;
                    endX = newX;
                    endY = newY;
                    break;
                }
                tiles[newX][newY]->setColor(Tile::Visited);
                q.push({newX, newY});
            }
        }

        delay(10);
    }

    if (found) {
        markPath(parent, tiles, endX, endY);
    }
}

bool Algorithms::isValid(int x, int y, Tile *tiles[Config::fieldSize][Config::fieldSize])
{
    if (x < 0 || y < 0 || x >= Config::fieldSize || y >= Config::fieldSize) {
        return false;
    }

    if (tiles[x][y]->getColor() == Tile::Wall || tiles[x][y]->getColor() == Tile::Visited) {
        return false;
    }
    return true;
}

void Algorithms::delay(int ms)
{
    QThread::msleep(ms);
    QApplication::processEvents();
}

void Algorithms::markPath(std::vector<std::vector<std::pair<int, int>>> &parent,
                          Tile *tiles[Config::fieldSize][Config::fieldSize],
                          int endX,
                          int endY)
{
    int x = endX, y = endY;
    while (tiles[x][y]->getColor() != Tile::Start) {
        delay(10);
        tiles[x][y]->setColor(Tile::Path);
        std::pair<int, int> p = parent[x][y];
        x = p.first;
        y = p.second;
    }
}
