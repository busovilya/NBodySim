#ifndef FORCE_H
#define FORCE_H

#include "SFML/Graphics.hpp"

class Force
{
private:
    sf::Vector2f direction;
public:
    Force(sf::Vector2f);
    sf::Vector2f getVector();
    const Force& operator+(const Force&);
    const Force& operator-(const Force&);
};

#endif