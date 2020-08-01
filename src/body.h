#ifndef BODY_H
#define BODY_H

#include <SFML/Graphics.hpp>
#include "force.h"

enum BodyState { NEW, CAPTURED, ACTIVE };

class Body
{
private:
    const float GRAVITY_CONSTANT = 10e-6;
    double mass;
    sf::Vector2f position;
    sf::Vector2f speed, acceleration;
    sf::CircleShape shape;
    BodyState state;
public:
    Body(double, double, BodyState initialState=NEW);
    sf::CircleShape* getShape();
    double getMass();
    double getRadius();
    void setMass(float mass);
    void setRadius(float radius);
    const sf::Vector2f& getPosition();
    void force(Force*);
    void move();
    void moveTo(float x, float y);
    void moveTo(sf::Vector2f position);
    sf::Vector2f getAcceleration();
    void setSpeed(sf::Vector2f);
    Force calcGravity(Body&);
    bool isCollided(Body&);
    void render(sf::RenderTarget*);
    BodyState getState();
    void setState(BodyState newState);
};

#endif