#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>
#include "body.h"
#include "simulation_window.h"
#include "math.h"
#include "button.h"
#include "text_panel.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "UniverseSim");
    sf::Keyboard keyboard;

    SimulationWindow simualtion(&window);

    while (window.isOpen())
    {        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
            // if(event.type == sf::Event::MouseButtonPressed)
            // {
            //     Body planet(100, 10);
            //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            //     planet.moveTo(mousePosition.x, mousePosition.y);
            //     planets.push_back(planet);
            // }
        }

        window.clear();

        simualtion.update(sf::Mouse::getPosition(window));
        simualtion.render(&window);
        
        window.display();
    }

    return 0;
}