#ifndef BODY_H
#define BODY_H

#include <SFML/Graphics.hpp>
#include "force.h"

class Body
{
private:
    const float GRAVITY_CONSTANT = 10e-6;
    double mass, radius;
    sf::Vector2f position;
    sf::Vector2f speed, acceleration;
    sf::CircleShape shape;
public:
    Body(double, double);
    sf::CircleShape* getShape();
    double getMass();
    double getRadius();
    const sf::Vector2f& getPosition();
    void force(Force*);
    void move();
    void moveTo(double, double);
    sf::Vector2f getAcceleration();
    void setSpeed(sf::Vector2f);
    Force calcGravity(Body&);
    bool isCollided(Body&);
    void render(sf::RenderTarget*);
};

#endif