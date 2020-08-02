#include <cmath>
#include <iostream>
#include "graphic_primitives.h"

Triangle::Triangle(sf::Vertex vertices[], sf::Color color)
{
    this->vertices = sf::VertexArray(sf::Triangles, 3);
    for(int i = 0; i < 3; i++)
        this->vertices[i] = vertices[i];

    this->color = color;    
    rotationAngle = 0;
}

void Triangle::render(sf::RenderTarget* target)
{
    target->draw(vertices);
}

Arrow::Arrow(sf::Vector2f position, sf::Vector2f direction, sf::Color color)
{
    line = sf::VertexArray(sf::Lines, 2);
    line[0] = sf::Vertex(position);
    line[1] = sf::Vertex(position + direction);
    double angle = atan(direction.y / direction.x);
    angle = direction.x > 0 ? M_PI + angle : angle;

    // TODO: magic number
    const double triangleSize = 5;
    sf::Vertex triangleVertices[] = {
        sf::Vector2f(line[1].position.x - triangleSize * cos(M_PI / 6), line[1].position.y + triangleSize * sin(M_PI / 6)),
        sf::Vector2f(line[1].position.x + triangleSize * cos(M_PI / 6), line[1].position.y + triangleSize * sin(M_PI / 6)),
        sf::Vector2f(line[1].position.x, line[1].position.y - triangleSize)
    };

    triangle = new Triangle(triangleVertices, sf::Color::White);
    triangle->setRotation(M_PI + M_PI_2 + angle);
    this->color = color;
}

void Arrow::render(sf::RenderTarget* target)
{
    target->draw(line);
    triangle->render(target);
}

Arrow::~Arrow()
{
    delete triangle;
}

void Triangle::setRotation(float angle)
{
    sf::Vector2f center(
        (vertices[0].position.x + vertices[1].position.x + vertices[2].position.x) / 3,
        (vertices[0].position.y + vertices[1].position.y + vertices[2].position.y) / 3
    );
    moveTo(sf::Vector2f(0, 0));
    rotationAngle = angle - rotationAngle;

    for(int i = 0; i < 3; i++)
    {
        vertices[i] = sf::Vertex(
            sf::Vector2f(vertices[i].position.x * cos(rotationAngle) - vertices[i].position.y * sin(rotationAngle),
                         vertices[i].position.x * sin(rotationAngle) + vertices[i].position.y * cos(rotationAngle))
        );
    }

    moveTo(center);
}

void Triangle::moveTo(sf::Vector2f position)
{
    sf::Vector2f center(
        (vertices[0].position.x + vertices[1].position.x + vertices[2].position.x) / 3,
        (vertices[0].position.y + vertices[1].position.y + vertices[2].position.y) / 3
    );

    for(int i = 0; i < 3; i++)
        vertices[i].position = position + vertices[i].position - center;
}