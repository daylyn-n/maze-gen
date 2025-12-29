#ifndef CELL_HPP
#define CELL_HPP
#include "../constants/constants.hpp"
enum Directions : u8
{
    N = 1, E = 2, S = 4, W = 8
};
struct Cell
{
    u8 walls = N | E | S | W;
    bool visited;
    bool hasWall(Directions d) const noexcept { return (walls& d) != 0; }
    void removeWall(Directions d) noexcept { walls &= static_cast<u8>(~d); }
    void addWall(Directions d) noexcept { walls |= d; }
};
#endif