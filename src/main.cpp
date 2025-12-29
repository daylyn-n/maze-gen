#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/algorithms.hpp"
#include "../include/grid.hpp"
#include "../constants/constants.hpp"




int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "MAZE");
    window.setFramerateLimit(60);
    // Grid grid(GRID_WIDTH, GRID_HEIGHT);
    // dfsMazeAnimation(grid, 0,0);
    
    sf::Vector2i previousPosition(-1, -1);

    // test for mouse position
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                std::cout << "Clicked" << std::endl;
            }
            if(event.type == sf::Event::Closed)
                window.close();
            
        }
         // Update mouse position every frame
        sf::Vector2i position = sf::Mouse::getPosition(window);

        if(position != previousPosition)
        {
            std::cout << "Mouse Position: " << position.x << ", " << position.y << std::endl;
            previousPosition = position;
        }
        
    }
}