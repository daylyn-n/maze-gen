#include <SFML/Graphics.hpp>
#include "../include/algorithms.hpp"
#include "../include/grid.hpp"
#include "../constants/constants.hpp"




int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "MAZE");
    window.setFramerateLimit(60);
    Grid grid(GRID_WIDTH, GRID_HEIGHT);
    dfsMazeAnimation(grid, 0,0);
}