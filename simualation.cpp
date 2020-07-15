#include <cmath>
#include "simulation.h"
#include "math.h"

Simulation::Simulation()
{
    Body planet1(20000, 25);
    planet1.moveTo(250, 250);

    Body planet2(200, 5);
    planet2.moveTo(200, 200);

    Body planet3(2000, 10);
    planet3.moveTo(350, 350);
    
    planets.push_back(planet1);
    planets.push_back(planet2);
    // planets.push_back(planet3);
};

void Simulation::addPlanet(const Body& body)
{
    planets.push_back(body);
};

std::vector<Body> Simulation::getPlanets()
{
    return planets;
};

bool Simulation::isCollided(Body& body1, Body& body2)
{
    return body1.getRadius() + body2.getRadius() >= getDistance(body1, body2);
};

double Simulation::getDistance(Body body1, Body body2)
{
    return distance(body1.getPosition(), body2.getPosition());
};