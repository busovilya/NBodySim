#include <cmath>
#include "math.h"
#include "body.h"

Body::Body(double mass, double radius, BodyState initialState)
{
    this->mass = mass;
    position = sf::Vector2f(0, 0);

    shape.setFillColor(sf::Color(46, 59, 240));
    shape.setRadius(radius);
    moveTo(position);

    state = initialState;
};

sf::CircleShape* Body::getShape()
{
    return &shape;
}

double Body::getMass()
{
    return mass;
};

void Body::setMass(float mass)
{
    this->mass = mass;
}

double Body::getRadius()
{
    return shape.getRadius();
};

void Body::setRadius(float radius)
{
    this->shape.setRadius(radius);
}

const sf::Vector2f& Body::getPosition()
{
    return position;
}

sf::Vector2f Body::getSpeed()
{
    return speed;
}

void Body::accelerate(sf::Vector2f acceleration)
{
    speed += acceleration;
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

// Force Body::calcGravity(Body& body)
// {
//     sf::Vector2f body1Position = this->getPosition();
//     sf::Vector2f body2Position = body.getPosition();
//     float dist = distance(body1Position, body2Position);
//     double forceValue = GRAVITY_CONSTANT * this->getMass() * body.getMass() / pow(dist, 2);
//     double xForce = forceValue * (body2Position.x - body1Position.x) / dist;
//     double yForce = forceValue * (body2Position.y - body1Position.y) / dist;
//     Force force(sf::Vector2f(xForce, yForce));
//     return force;
// }

bool Body::isCollided(Body& body)
{
    return this->getRadius() + body.getRadius() >= distance(this->getPosition(), body.getPosition());
};

void Body::render(sf::RenderTarget* target)
{
    if(state == NEW || state == CAPTURED)
        shape.setFillColor(sf::Color(66, 22, 210));    
    else
        shape.setFillColor(sf::Color(46, 59, 240));
    target->draw(shape);
}

void Body::setState(BodyState newState)
{
    state = newState;
}

BodyState Body::getState()
{
    return state;
}