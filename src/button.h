#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

enum ButtonStates{IDLE_BTN=0, PRESSED_BTN=1};

class Button
{
private:
    ButtonStates state;

    sf::Text text;
    sf::Font* font;
    sf::RectangleShape rect;

    sf::Color idleColor;
    sf::Color pressedColor;
public:
    Button(int, int, int, int, std::string, sf::Font*, sf::Color, sf::Color);
    ~Button();
    void render(sf::RenderTarget*);
    void update(sf::Vector2i);
    sf::IntRect getRect();
};

#endif