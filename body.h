#ifndef BODY_H
#define BODY_H

#include <SFML/Graphics.hpp>
#include "force.h"

class Body
{
private:
    double mass, radius;
    sf::Vector2f position;
    sf::Vector2f speed, acceleration;
public:
    Body(double, double);
    double getMass();
    double getRadius();
    const sf::Vector2f& getPosition();
    void force(Force*);
    void move();
    void moveTo(double, double);
    sf::Vector2f getAcceleration();
    void setSpeed(sf::Vector2f);
};

#endif