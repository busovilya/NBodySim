#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "body.h"
#include "simulation.h"

sf::CircleShape getBodyShape(Body body)
{
    sf::CircleShape shape(body.getRadius());
    shape.setFillColor(sf::Color::Red);
    shape.move(sf::Vector2f(body.getX(), body.getY()));
    return shape;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "GravitySim");
    sf::Keyboard keyboard;

    Simulation simualtion;
    std::vector<Body> planets = simualtion.getPlanets();
    planets[1].force(new Force(sf::Vector2f(5, -10)));
    planets[2].force(new Force(sf::Vector2f(0, -100)));

    while (window.isOpen())
    {        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed)
            {
                Body planet(100, 10);
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                planet.moveTo(mousePosition.x, mousePosition.y);
                planets.push_back(planet);
            }
        }

        window.clear();

        for(int i = 0; i < planets.size(); i++)
        {
            Force totalForce(sf::Vector2f(0, 0));
            for(int j = 0; j < planets.size(); j++)
            {
                if(i != j)
                {
                    double distance = sqrt(pow(planets[i].getX() - planets[j].getX(), 2) + pow(planets[i].getY() - planets[j].getY(), 2));
                    double forceValue = 0.00001 * planets[i].getMass() * planets[j].getMass() / pow(distance, 2);
                    double xForce = forceValue * (planets[j].getX() - planets[i].getX()) / distance;
                    double yForce = forceValue * (planets[j].getY() - planets[i].getY()) / distance;
                    Force force(sf::Vector2f(xForce, yForce));
                    totalForce = totalForce + force;
                }
            }
            

            planets[i].force(&totalForce);
            planets[i].move();
            window.draw(getBodyShape(planets[i]));
        }
        window.display();
    }

    return 0;
}