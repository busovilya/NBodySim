#include "simulation_window.h"
#include "body.h"
#include "text_panel.h"
#include "button.h"
#include <vector>
#include <iostream>

SimulationWindow::SimulationWindow(sf::RenderWindow* target)
{
    window = target;

    sf::Font* font = new sf::Font();
    initFont(font);
    
    Button* button = new Button(550, 10, 80, 50, "Add button", font, sf::Color::Blue, sf::Color::Cyan);
    buttons.push_back(button);

    TextPanel* textPanel = new TextPanel(sf::Vector2f(540, 80), sf::Vector2f(80, 30), "", font, 12, TextHorizontalAlign::LEFT);
    textPanels.push_back(textPanel);
    textPanel = new TextPanel(sf::Vector2f(540, 120), sf::Vector2f(80, 30), "", font, 12, TextHorizontalAlign::LEFT);
    textPanels.push_back(textPanel);

    int widgetsPanelWidth = 100;
    widgetsPanel.setFillColor(sf::Color::White);
    widgetsPanel.setPosition(sf::Vector2f(window->getSize().x - widgetsPanelWidth, 0));
    widgetsPanel.setSize(sf::Vector2f(widgetsPanelWidth, window->getSize().y));

}

void SimulationWindow::update(sf::Vector2i mousePosition)
{
    std::vector<Body>& planets = simulation.getPlanets(); 
    selectedBody = nullptr;

    for(int i = 0; i < planets.size(); i++)
    {
        Force totalForce(sf::Vector2f(0, 0));
        for(int j = 0; j < planets.size(); j++)
        {
            if(i != j)
            {
                Force force = planets[i].calcGravity(planets[j]);
                totalForce = totalForce + force;

                if(planets[i].isCollided(planets[j]))
                {
                    simulation.processColision(planets[i], planets[j]);
                    break;
                }
            }
        }

        // std::cout << sf::Mouse::getPosition(*window).x << ' ' << sf::Mouse::getPosition(*window).y << std::endl;
        if(planets[i].getShape()->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
        {
            selectedBody = &planets[i];
        }
        planets[i].force(&totalForce);
        planets[i].move();
    }

    for(Button* button: buttons)
        button->update(mousePosition);

    if(selectedBody != nullptr)
    {
        textPanels[0]->update("Radius: " + std::to_string(int(selectedBody->getRadius())));
        textPanels[1]->update("Mass: " + std::to_string(int(selectedBody->getMass())));
    }
    else
        for(TextPanel* textPanel: textPanels)
            textPanel->update("");
}

void SimulationWindow::render(sf::RenderTarget* target)
{
    target->draw(widgetsPanel);

    std::vector<Body>& planets = simulation.getPlanets(); 
    for(int i = 0; i < planets.size(); i++)
        planets[i].render(target);

    for(Button* button: buttons)
        button->render(target);

    for(TextPanel* textPanel: textPanels)
        textPanel->render(target);    
}


void SimulationWindow::initFont(sf::Font* font)
{
    if(!font->loadFromFile("./res/fonts/Ubuntu-B.ttf"))
    {
        std::cout << "Can't load fonts!" << std::endl;
    }
}