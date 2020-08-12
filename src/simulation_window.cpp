#include "simulation_window.h"
#include "body.h"
#include "text_panel.h"
#include "button.h"
#include "math.h"
#include "graphic_primitives.h"
#include "config_parser.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>

SimulationWindow::SimulationWindow(int argc, char *argv[])
{
    window.create(sf::VideoMode(960, 680), "UniverseSim", sf::Style::Close);

    sf::Font *font = new sf::Font();
    initFont(font);

    bodyInfo = new TextPanel(sf::Vector2f(window.getSize().x - 90, 10), sf::Vector2f(80, 30), "", font, 12, sf::Color::White, TextHorizontalAlign::LEFT);
    state = DEFAULT;
    capturedBody = nullptr;

    if (argc > 1)
    {
        char *filename = argv[1];
        std::fstream configFile(filename);
        if (configFile.good())
        {
            configFile.close();
            ConfigParser parser(filename);
            std::vector<BodyData> bodiesData = parser.Parse();
            for (BodyData data : bodiesData)
            {
                Body *newPlanet = new Body(data.mass, data.radius, ACTIVE);
                newPlanet->moveTo(data.position.x, data.position.y);
                newPlanet->setSpeed(sf::Vector2f(data.speed.x, data.speed.y));
                simulation.addPlanet(newPlanet);
            }
        }
        else
        {
            std::cout << "Can't open config file!" << std::endl;
        }
    }
}

void SimulationWindow::runSimulation()
{
    while (window.isOpen())
    {
        listenEvents();
        window.clear();

        update(sf::Mouse::getPosition(window));
        render();

        window.display();
    }
}

void SimulationWindow::listenEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            if (state == ADD_PLANET)
            {
                simulation.removePlanet(capturedBody);
                state = DEFAULT;
            }
            if (state != ADD_PLANET)
                releaseBody();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
        {
            if (state == DEFAULT)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (capturedBody == nullptr)
                {
                    state = ADD_PLANET;
                    Body *newPlanet = new Body(100, 20);
                    newPlanet->setState(NEW);
                    capturedBody = newPlanet;
                    newPlanet->moveTo(sf::Vector2f(mousePosition));
                    simulation.addPlanet(newPlanet);
                }
            }
        }

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            // Change body mass if selected
            if (capturedBody != nullptr)
            {
                double capturedBodyMass = capturedBody->getMass();
                float delta = event.mouseWheelScroll.delta;
                capturedBody->setMass(std::max(10., capturedBodyMass + delta));
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            if (dragAndDrop.active)
            {
                dragAndDrop.direction = sf::Mouse::getPosition() - dragAndDrop.startPosition;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            dragAndDrop.active = true;
            dragAndDrop.startPosition = sf::Mouse::getPosition();
            dragAndDrop.mouseButton = event.mouseButton.button;

            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            if (dragAndDrop.mouseButton == event.mouseButton.button)
            {
                if (capturedBody != nullptr)
                {
                    // Update body radius if mouse dragged with pressed right button
                    if (dragAndDrop.mouseButton == sf::Mouse::Right)
                    {
                        double bodyRadius = capturedBody->getRadius();
                        double multiplier = dragAndDrop.direction.y > 0 ? 0.1 : -0.1;
                        double x = norm(sf::Vector2f(dragAndDrop.direction));
                        capturedBody->setRadius(std::max(10., bodyRadius + multiplier * norm(sf::Vector2f(dragAndDrop.direction))));

                        for (Body *body : simulation.getPlanets())
                            if (body->isCollided(*capturedBody) && capturedBody != body)
                            {
                                capturedBody->setRadius(bodyRadius);
                                break;
                            }
                    }
                    else if (dragAndDrop.mouseButton == sf::Mouse::Left)
                    {
                        sf::Vector2f acceleration(sf::Vector2f(dragAndDrop.direction) * -0.1f / (float)capturedBody->getMass());

                        bool canAddBody = true;
                        for (Body *body : simulation.getPlanets())
                            if (body != capturedBody)
                                if (capturedBody->isCollided(*body))
                                    canAddBody = false;

                        if (canAddBody && state == ADD_PLANET || state == DEFAULT)
                        {
                            capturedBody->accelerate(acceleration);
                            releaseBody();
                            state = DEFAULT;
                        }
                    }
                }
                else
                {
                    if (event.mouseButton.button == sf::Mouse::Button::Left)
                        if (capturedBody == nullptr)
                            for (Body *body : simulation.getPlanets())
                                if (body->getShape()->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                                {
                                    releaseBody();
                                    captureBody(body);
                                    break;
                                }
                }
                dragAndDrop.reset();
            }
        }
    }
}

void SimulationWindow::update(sf::Vector2i mousePosition)
{
    std::vector<Body *> &planets = simulation.getPlanets();
    if (state != ADD_PLANET && !dragAndDrop.active)
        selectedBody = nullptr;

    simulation.processSystem();

    for (int i = 0; i < planets.size(); i++)
        if (planets[i]->getShape()->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        {
            selectedBody = planets[i];
        }

    if (selectedBody != nullptr)
    {
        bodyInfo->update("Radius: " + std::to_string(int(selectedBody->getRadius())) + '\n' + "Mass: " + std::to_string(int(selectedBody->getMass())));
    }
    else
        bodyInfo->update("");

    if (capturedBody != nullptr)
        if (capturedBody->getState() == NEW)
            if (!dragAndDrop.active)
                capturedBody->moveTo(sf::Vector2f(mousePosition));
}

void SimulationWindow::render()
{
    if (dragAndDrop.active && capturedBody != nullptr && dragAndDrop.mouseButton == sf::Mouse::Left)
    {
        Arrow arrow(sf::Vector2f(capturedBody->getPosition()), sf::Vector2f(dragAndDrop.direction) * -1.0f, sf::Color::White);
        arrow.render(&window);
    }
    std::vector<Body *> &planets = simulation.getPlanets();
    for (int i = 0; i < planets.size(); i++)
        planets[i]->render(&window);

    bodyInfo->render(&window);
}

void SimulationWindow::initFont(sf::Font *font)
{
    if (!font->loadFromFile("./res/fonts/Ubuntu-B.ttf"))
    {
        std::cout << "Can't load fonts!" << std::endl;
    }
}

void printVector(const sf::Vector2f &vector)
{
    std::cout << vector.x << ' ' << vector.y << std::endl;
}

bool SimulationWindow::intersect(const sf::RectangleShape &rect, const sf::CircleShape &circle)
{
    return rect.getGlobalBounds().contains(circle.getPosition().x, circle.getPosition().y) &&
           rect.getGlobalBounds().contains(circle.getPosition().x + 2 * circle.getRadius(), circle.getPosition().y + 2 * circle.getRadius());
}

void SimulationWindow::captureBody(Body *body)
{
    capturedBody = body;
    capturedBody->setState(CAPTURED);
}

void SimulationWindow::releaseBody()
{
    if (capturedBody != nullptr)
    {
        capturedBody->setState(ACTIVE);
        capturedBody = nullptr;
    }
}

SimulationWindow::~SimulationWindow()
{
    for (Body *body : simulation.getPlanets())
        delete body;
    delete bodyInfo;
}