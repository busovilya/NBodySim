#include <cmath>
#include "math.h"
#include "body.h"

Body::Body(double mass, double radius)
{
    this->mass = mass;
    this->radius = radius;
    position = sf::Vector2f(0, 0);

    shape.setFillColor(sf::Color::Blue);
    shape.setRadius(radius);
    moveTo(position);

    interaction = true;
};

sf::CircleShape* Body::getShape()
{
    return &shape;
}

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
    moveTo(position.x + speed.x, position.y + speed.y);
}


void Body::moveTo(float x, float y)
{
    position.x = x;
    position.y = y;
    shape.setPosition(position.x - getRadius(), position.y - getRadius());
}

void Body::moveTo(sf::Vector2f position)
{
    moveTo(position.x, position.y);
}


void Body::setSpeed(sf::Vector2f vector)
{
    speed = vector;
}

Force Body::calcGravity(Body& body)
{
    sf::Vector2f body1Position = this->getPosition();
    sf::Vector2f body2Position = body.getPosition();
    float dist = distance(body1Position, body2Position);
    double forceValue = GRAVITY_CONSTANT * this->getMass() * body.getMass() / pow(dist, 2);
    double xForce = forceValue * (body2Position.x - body1Position.x) / dist;
    double yForce = forceValue * (body2Position.y - body1Position.y) / dist;
    Force force(sf::Vector2f(xForce, yForce));
    return force;
}

bool Body::isCollided(Body& body)
{
    return this->getRadius() + body.getRadius() >= distance(this->getPosition(), body.getPosition());
};

void Body::render(sf::RenderTarget* target)
{
    target->draw(shape);
}

void Body::interactionOn()
{
    interaction = true;
}

void Body::interactionOff()
{
    interaction = false;
}

bool Body::getInteraction()
{
    return interaction;
}