#include <SFML/Graphics.hpp>

class Triangle
{
private:
    sf::VertexArray vertices;
    sf::Color color;
    double rotationAngle;
public:
    Triangle(sf::Vertex vertices[], sf::Color color);
    void render(sf::RenderTarget* target);
    void setRotation(float angle);
    void moveTo(sf::Vector2f position);
};

class Arrow
{
private:
    sf::VertexArray line;
    Triangle* triangle;
    sf::Color color;
public:
    Arrow(sf::Vector2f position, sf::Vector2f direction, sf::Color color);
    void render(sf::RenderTarget* target);
    ~Arrow();
};
