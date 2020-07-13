#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "body.h"

class Simulation
{
private:
    std::vector<Body> planets;
    double getDistance(Body, Body);
public:
    Simulation();
    void addPlanet(const Body&);
    std::vector<Body> getPlanets();
    bool isCollided(Body, Body);
};

#endif