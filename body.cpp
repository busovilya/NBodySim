#include "body.h"

Body::Body(double mass, double radius)
{
    this->mass = mass;
    this->radius = radius;
    x = 100;
    y = 100;
};

double Body::getMass()
{
    return mass;
};

double Body::getRadius()
{
    return radius;
};

int Body::getX()
{
    return x;
};

int Body::getY()
{
    return y;
};

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
    x += speed.x;
    y += speed.y;
}


void Body::moveTo(double x, double y)
{
    this->x = x;
    this->y = y;
}
