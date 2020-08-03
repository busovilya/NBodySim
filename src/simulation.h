#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "body.h"

class Simulation
{
private:
    std::vector<Body*> planets;
    double getDistance(Body&, Body&);
    const float GRAVITY_CONSTANT = 10e-4;
public:
    Simulation();
    void addPlanet(Body*);
    void removePlanet(Body*);
    std::vector<Body*>& getPlanets();
    void processColision(Body&, Body&);
    void processSystem();
};

#endif