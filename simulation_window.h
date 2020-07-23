#ifndef SIMULATION_WINDOW
#define SIMULATION_WINDOW

#include "simulation.h"
#include "button.h"
#include "text_panel.h"
#include <vector>
#include <SFML/Graphics.hpp>

enum SimulationWindowState { DEFAULT, ADD_PLANET };

class SimulationWindow
{
private:
    Simulation simulation;
    sf::RenderWindow* window;
    std::vector<Button*> buttons;
    std::vector<TextPanel*> textPanels;
    sf::RectangleShape widgetsPanel;
    Body* selectedBody;
    void initFont(sf::Font* font);
    SimulationWindowState state;
public:
    SimulationWindow(sf::RenderWindow* target);
    void runSimulation();
    void update(sf::Vector2i mousePosition);
    void render(sf::RenderTarget* target);
};

#endif