#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "body.h"

sf::CircleShape getBodyShape(Body body)
{
    sf::CircleShape shape(body.getRadius());
    shape.setFillColor(sf::Color::Red);
    shape.move(sf::Vector2f(body.getX(), body.getY()));
    return shape;
}

std::vector<Body> getPlanets()
{
    Body planet1(20000, 25);
    planet1.moveTo(250, 250);

    Body planet2(200, 5);
    planet2.moveTo(200, 200);

    Body planet3(2000, 10);
    planet3.moveTo(350, 350);
    
    std::vector<Body> planets;
    planets.push_back(planet1);
    planets.push_back(planet2);
    planets.push_back(planet3);
    return planets;
}

double getDistance(Body* body1, Body* body2)
{
    return sqrt(pow(body1->getX() - body2->getX(), 2) + pow(body1->getY() - body2->getY(), 2));
}

bool isCollided(Body* body1, Body* body2)
{
    return body1->getRadius() + body2->getRadius() >= getDistance(body1, body2);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "GravitySim");
    sf::Keyboard keyboard;
    std::vector<Body> planets = getPlanets();
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