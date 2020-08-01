#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "body.h"

class Simulation
{
private:
    std::vector<Body*> planets;
    double getDistance(Body&, Body&);
public:
    Simulation();
    void addPlanet(Body*);
    std::vector<Body*>& getPlanets();
    void processColision(Body&, Body&);
};

#endif