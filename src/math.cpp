#include "math.h"

float norm(const sf::Vector2f& vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
    return norm(vector2 - vector1);
}