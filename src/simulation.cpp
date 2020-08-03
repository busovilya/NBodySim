#include <cmath>
#include <algorithm>
#include "simulation.h"
#include "math.h"

Simulation::Simulation()
{
    Body* planet1 = new Body(20000, 15, ACTIVE);
    planet1->moveTo(350, 350);
    // planet1->setSpeed(sf::Vector2f(0, -0.01));

    Body* planet2 = new Body(200, 15, ACTIVE);
    planet2->moveTo(350, 250);
    planet2->setSpeed(sf::Vector2f(sqrt(2 * GRAVITY_CONSTANT * planet1->getMass() / 100.0 / 1.5) , 0));
    
    // planets.push_back(planet1);
    // planets.push_back(planet2);
};

void Simulation::addPlanet(Body* body)
{
    planets.push_back(body);
};

void Simulation::removePlanet(Body* body)
{
    planets.erase(std::remove(planets.begin(), planets.end(), body), planets.end());
    delete body;
};

std::vector<Body*>& Simulation::getPlanets()
{
    return planets;
};

void Simulation::processColision(Body& body1, Body& body2)
{
    body1.setSpeed(sf::Vector2f(0, 0));
    body2.setSpeed(sf::Vector2f(0, 0));
}


void Simulation::processSystem()
{
    for(int i = 0; i < planets.size(); i++)
    {
        sf::Vector2f totalAccel(0, 0);
        for(int j = 0; j < planets.size(); j++)
        {
            if(planets[i]->getState() == NEW || planets[j]->getState() == NEW)
                continue;
            if(i != j)
            {
                if(planets[i]->isCollided(*planets[j]))
                {
                    processColision(*planets[i], *planets[j]);
                    break;
                }
                totalAccel += (planets[j]->getPosition() - planets[i]->getPosition()) * GRAVITY_CONSTANT * (float)planets[j]->getMass() / 
                              (float)pow(norm(planets[j]->getPosition() - planets[i]->getPosition()), 3);
            }
        }
        planets[i]->moveTo(planets[i]->getPosition() + planets[i]->getSpeed());
        planets[i]->setSpeed(planets[i]->getSpeed() + totalAccel);
    }
}