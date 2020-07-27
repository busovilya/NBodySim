#include "force.h"

Force::Force(sf::Vector2f vector)
{
    direction = vector;
}

sf::Vector2f Force::getVector()
{
    return direction;
};

const Force& Force::operator+(const Force& force)
{
    direction += force.direction;
    return *this;
};

const Force& Force::operator-(const Force& force)
{
    direction -= force.direction;
    return *this;
};