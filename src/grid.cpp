#include "../include/grid.hpp"

Grid::Grid(int width, int height)
{
    cells.resize(height, std::vector<Cell>(width));
    initialize();
}

void Grid::initialize()
{
    for(int y{}; y < GRID_HEIGHT; y++)
    {
        for(int x{}; x < GRID_WIDTH; x++)
        {
            cells[y][x].walls = N | E | S | W;
            cells[y][x].visited = false;
        }
    }
}

Cell& Grid::getCell(int x, int y)
{
    return cells[y][x];
}
const Cell& Grid::getCell(int x, int y) const
{
    return cells[y][x];
}
float Grid::getWidth() const
{
    return GRID_WIDTH;
}
float Grid::getHeight() const
{
    return GRID_HEIGHT;
}