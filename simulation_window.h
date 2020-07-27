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
    sf::RenderWindow window;
    std::vector<Button*> buttons;
    std::vector<TextPanel*> textPanels;
    sf::RectangleShape spaceArea;
    sf::RectangleShape widgetsPanel;
    Body* selectedBody;
    void initFont(sf::Font* font);
    SimulationWindowState state;
    bool intersect(const sf::RectangleShape&, const sf::CircleShape&);
public:
    SimulationWindow();
    void runSimulation();
    void update(sf::Vector2i mousePosition);
    void render();
};

#endif