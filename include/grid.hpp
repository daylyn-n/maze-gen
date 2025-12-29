#ifndef GRID_HPP
#define GRID_HPP
#include "cell.hpp"
#include "../constants/constants.hpp"
#include <vector>

class Grid
{
private:
    std::vector<std::vector<Cell>> cells;

public:
    Grid(int width, int height);
    void initialize();
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;
    float getWidth() const;
    float getHeight() const;
};

#endif