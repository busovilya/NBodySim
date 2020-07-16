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

double Simulation::getDistance(Body& body1, Body& body2)
{
    return distance(body1.getPosition(), body2.getPosition());
};

Force Simulation::calcGravity(Body& body1, Body& body2)
{
    sf::Vector2f body1Position = body1.getPosition();
    sf::Vector2f body2Position = body2.getPosition();
    float dist = distance(body1Position, body2Position);
    double forceValue = GRAVITY_CONSTANT * body1.getMass() * body2.getMass() / pow(dist, 2);
    double xForce = forceValue * (body2Position.x - body1Position.x) / dist;
    double yForce = forceValue * (body2Position.y - body1Position.y) / dist;
    Force force(sf::Vector2f(xForce, yForce));
    return force;
}

void Simulation::processColision(Body& body1, Body& body2)
{
    body1.setSpeed(sf::Vector2f(0, 0));
    body2.setSpeed(sf::Vector2f(0, 0));
}