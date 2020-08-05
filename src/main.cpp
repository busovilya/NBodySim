#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>
#include "body.h"
#include "simulation_window.h"
#include "math.h"
#include "button.h"
#include "text_panel.h"
#include "yaml/Yaml.hpp"

int main(int argc, char *argv[])
{     
    SimulationWindow simualtion(argc, argv);
    simualtion.runSimulation();
    return 0;
}