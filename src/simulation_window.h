#ifndef SIMULATION_WINDOW
#define SIMULATION_WINDOW

#include "simulation.h"
#include "button.h"
#include "text_panel.h"
#include <vector>
#include <SFML/Graphics.hpp>

enum SimulationWindowState { DEFAULT, ADD_PLANET };

struct DragAndDropData
{
    sf::Mouse::Button mouseButton;
    sf::Vector2i startPosition;
    sf::Vector2i direction;
    bool active;

    DragAndDropData()
    {
        reset();
    }

    void reset()
    {
        startPosition = sf::Vector2i(0, 0);
        direction = sf::Vector2i(0, 0);
        active = false;
    }
};

class SimulationWindow
{
private:
    Simulation simulation;
    sf::RenderWindow window;
    TextPanel* bodyInfo;
    sf::RectangleShape widgetsPanel;
    Body* selectedBody;
    Body* capturedBody;
    void initFont(sf::Font* font);
    SimulationWindowState state;
    DragAndDropData dragAndDrop;
    bool intersect(const sf::RectangleShape&, const sf::CircleShape&);
    void captureBody(Body*);
    void releaseBody();
    sf::Clock clock;
    int FPS = 45;
public:
    SimulationWindow(int, char*[]);
    void runSimulation();
    void listenEvents();
    void update(sf::Vector2i mousePosition);
    void render();
    ~SimulationWindow();
};

#endif