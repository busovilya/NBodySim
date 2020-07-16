#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "body.h"

class Simulation
{
private:
    const float GRAVITY_CONSTANT = 10e-6;
    std::vector<Body> planets;
    double getDistance(Body&, Body&);
public:
    Simulation();
    void addPlanet(const Body&);
    std::vector<Body> getPlanets();
    bool isCollided(Body&, Body&);
    Force calcGravity(Body&, Body&);
    void processColision(Body&, Body&);
};

#endif