#include "body.h"

Body::Body(double mass, double radius)
{
    this->mass = mass;
    this->radius = radius;
    position = sf::Vector2f(0, 0);
};

double Body::getMass()
{
    return mass;
};

double Body::getRadius()
{
    return radius;
};

const sf::Vector2f& Body::getPosition()
{
    return position;
}

sf::Vector2f Body::getAcceleration()
{
    return acceleration;
}

void Body::force(Force* force)
{
    acceleration.x = force->getVector().x / mass;
    acceleration.y = force->getVector().y / mass;
    speed.x += acceleration.x;
    speed.y += acceleration.y;
}

void Body::move()
{
    position.x += speed.x;
    position.y += speed.y;
}


void Body::moveTo(double x, double y)
{
    position.x = x;
    position.y = y;
}


void Body::setSpeed(sf::Vector2f vector)
{
    speed = vector;
}