#include <cmath>
#include "simulation.h"
#include "math.h"

Simulation::Simulation()
{
    Body* planet1 = new Body(20000, 25, ACTIVE);
    planet1->moveTo(250, 250);

    Body* planet2 = new Body(200, 5, ACTIVE);
    planet2->moveTo(200, 200);
    
    planets.push_back(planet1);
    planets.push_back(planet2);

    planets[1]->force(new Force(sf::Vector2f(5, -10)));
};

void Simulation::addPlanet(Body* body)
{
    planets.push_back(body);
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