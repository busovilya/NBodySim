#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "body.h"
#include "simulation.h"
#include "math.h"
#include "button.h"

sf::CircleShape getBodyShape(Body body)
{
    sf::CircleShape shape(body.getRadius());
    shape.setFillColor(sf::Color::Blue);
    shape.move(sf::Vector2f(body.getPosition().x - body.getRadius(), body.getPosition().y - body.getRadius()));
    return shape;
}

void initFont(sf::Font* font)
{
    if(!font->loadFromFile("./res/fonts/Ubuntu-B.ttf"))
    {
        std::cout << "Can't load fonts!" << std::endl;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "UniverseSim");
    sf::Keyboard keyboard;

    Simulation simualtion;
    std::vector<Body> planets = simualtion.getPlanets();
    planets[1].force(new Force(sf::Vector2f(5, -10)));
    // planets[1].force(new Force(sf::Vector2f(25, 0)));

    sf::Font font;
    initFont(&font);

    sf::Text text;
    text.setString("Add planet");
    text.setFillColor(sf::Color::Black);
    Button buttons[] = {Button(550, 10, 80, 50, text, &font, sf::Color::Blue, sf::Color::Cyan)};

    sf::RectangleShape rightPanel;
    int rightPanelWidth = 100;
    rightPanel.setFillColor(sf::Color::White);
    rightPanel.setPosition(sf::Vector2f(window.getSize().x - rightPanelWidth, 0));
    rightPanel.setSize(sf::Vector2f(rightPanelWidth, window.getSize().y));

    while (window.isOpen())
    {        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
            // if(event.type == sf::Event::MouseButtonPressed)
            // {
            //     Body planet(100, 10);
            //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            //     planet.moveTo(mousePosition.x, mousePosition.y);
            //     planets.push_back(planet);
            // }
        }

        window.clear();
        window.draw(rightPanel);

        for(int i = 0; i < planets.size(); i++)
        {
            Force totalForce(sf::Vector2f(0, 0));
            for(int j = 0; j < planets.size(); j++)
            {
                if(i != j)
                {
                    Force force = simualtion.calcGravity(planets[i], planets[j]);
                    totalForce = totalForce + force;

                    if(simualtion.isCollided(planets[i], planets[j]))
                    {
                        simualtion.processColision(planets[i], planets[j]);
                        break;
                    }
                }
            }

            sf::Vector2f unitAccel = planets[i].getAcceleration() / norm(planets[i].getAcceleration());
            sf::Vertex line[] = {
                planets[i].getPosition(),
                planets[i].getPosition() + unitAccel * 10.0f
            };
            window.draw(line, 2, sf::Lines);
            planets[i].force(&totalForce);
            planets[i].move();

            if(!rightPanel.getGlobalBounds().contains(planets[i].getPosition().x,
                                                      planets[i].getPosition().y))
                window.draw(getBodyShape(planets[i]));

        }
        for(int i = 0; i < 1; i++)
        {
            buttons[i].update(sf::Mouse::getPosition(window));
            buttons[i].render(&window);
        }
        window.display();
    }

    return 0;
}