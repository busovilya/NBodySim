#include <SFML/Graphics.hpp>
#include "force.h"

class Body
{
private:
    double mass, radius;
    double x, y;
    sf::Vector2f speed, acceleration;
public:
    Body(double, double);
    double getMass();
    double getRadius();
    int getX();
    int getY();
    void force(Force*);
    void move();
    void moveTo(double, double);
    sf::Vector2f getAcceleration();
};