#include "simulation_window.h"
#include "body.h"
#include "text_panel.h"
#include "button.h"
#include "math.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>

SimulationWindow::SimulationWindow()
{
    window.create(sf::VideoMode(640, 480), "UniverseSim");

    sf::Font *font = new sf::Font();
    initFont(font);

    addButton = new Button(550, 10, 80, 50, "Add planet", font, sf::Color::Blue, sf::Color::Magenta);

    bodyInfo = new TextPanel(sf::Vector2f(540, 80), sf::Vector2f(80, 30), "", font, 12, TextHorizontalAlign::LEFT);

    int widgetsPanelWidth = 100;
    widgetsPanel.setFillColor(sf::Color::White);
    widgetsPanel.setPosition(sf::Vector2f(window.getSize().x - widgetsPanelWidth, 0));
    widgetsPanel.setSize(sf::Vector2f(widgetsPanelWidth, window.getSize().y));

    spaceArea.setPosition(0, 0);
    spaceArea.setSize(sf::Vector2f(window.getSize().x - widgetsPanelWidth, window.getSize().y));

    state = DEFAULT;

    capturedBody = nullptr;
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
            if (state != ADD_PLANET)
                releaseBody();
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
                if (state == DEFAULT)
                {
                    if (addButton->getRect().contains(sf::Mouse::getPosition(window)))
                    {
                        state = ADD_PLANET;
                        Body *newPlanet = new Body(100, 20);
                        newPlanet->setState(NEW);
                        capturedBody = newPlanet;
                        simulation.addPlanet(newPlanet);
                    }
                    else
                    {
                        for (Body *body : simulation.getPlanets())
                            if (body->getShape()->getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                            {
                                releaseBody();
                                captureBody(body);
                                break;
                            }
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            if (dragAndDrop.mouseButton == event.mouseButton.button)
            {
                dragAndDrop.active = false;

                if (capturedBody != nullptr)
                {
                    // Update body radius if mouse dragged with pressed right button
                    if (dragAndDrop.mouseButton == sf::Mouse::Right)
                    {
                        double bodyRadius = capturedBody->getRadius();
                        double multiplier = dragAndDrop.direction.y > 0 ? 0.1 : -0.1;
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
                        if (spaceArea.getGlobalBounds().contains(sf::Vector2f(mousePosition)))
                        {
                            Force force(sf::Vector2f(dragAndDrop.direction) * -0.1f);
                            capturedBody->force(&force);
                        }

                        if (state == ADD_PLANET)
                        {
                            if (capturedBody == nullptr)
                                throw std::runtime_error("capturedBody can't be NULL! at line number " + std::to_string(__LINE__));
                            bool canAddBody = true;
                            for (Body *body : simulation.getPlanets())
                                if (body != capturedBody)
                                    if (capturedBody->isCollided(*body))
                                        canAddBody = false;

                            if (!intersect(spaceArea, *capturedBody->getShape()))
                                canAddBody = false;

                            if (canAddBody)
                            {
                                releaseBody();
                                state = DEFAULT;
                            }
                        }
                    }
                }
            }
        }
    }
}

void SimulationWindow::update(sf::Vector2i mousePosition)
{
    std::vector<Body *> &planets = simulation.getPlanets();
    if (state != ADD_PLANET && !dragAndDrop.active)
        selectedBody = nullptr;

    for (int i = 0; i < planets.size(); i++)
    {
        Force totalForce(sf::Vector2f(0, 0));
        for (int j = 0; j < planets.size(); j++)
        {
            if (i != j)
            {
                if (planets[i]->getState() == NEW || planets[j]->getState() == NEW)
                    continue;
                Force force = planets[i]->calcGravity(*planets[j]);
                totalForce = totalForce + force;

                if (planets[i]->isCollided(*planets[j]))
                {
                    simulation.processColision(*planets[i], *planets[j]);
                    break;
                }
            }
        }

        if (planets[i]->getShape()->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        {
            selectedBody = planets[i];
        }
        planets[i]->force(&totalForce);
        planets[i]->move();
    }

    addButton->update(mousePosition);

    if (selectedBody != nullptr)
    {
        bodyInfo->update("Radius: " + std::to_string(int(selectedBody->getRadius())) + '\n' 
                        + "Mass: " + std::to_string(int(selectedBody->getMass())));
    }
    else
        bodyInfo->update("");

    if (capturedBody != nullptr)
        if (capturedBody->getState() == NEW)
            if(!dragAndDrop.active)
                capturedBody->moveTo(sf::Vector2f(mousePosition));
}

void SimulationWindow::render()
{
    // window.draw(spaceArea);
    window.draw(widgetsPanel);

    std::vector<Body *> &planets = simulation.getPlanets();
    for (int i = 0; i < planets.size(); i++)
        if (intersect(spaceArea, *planets[i]->getShape()))
            planets[i]->render(&window);

    addButton->render(&window);
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
    for(Body* body: simulation.getPlanets())
        delete body;
    delete addButton;
    delete bodyInfo;
}