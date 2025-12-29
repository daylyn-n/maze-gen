#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "algorithms.hpp"
#include "../constants/constants.hpp"

struct ClickResult
{
    int x, y;
    bool clicked;
};
static ClickResult getClickedCell(const sf::Vector2i& mousePos, const Grid& grid);
void solver(Grid& grid, int startX, int startY);

#endif