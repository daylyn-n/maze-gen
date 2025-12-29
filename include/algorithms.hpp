#ifndef ALGORITHMS_HPP
#define ALGORIRTHMS_HPP
#include "grid.hpp"
#include <queue>
#include <SFML/Graphics.hpp>
#include "../constants/constants.hpp"
void dfsMaze(Grid& grid, int startX, int startY);
void dfsMazeAnimation(Grid& grid, int startX, int startY);
static void drawGrid(sf::RenderWindow& window, const Grid& grid);
#endif