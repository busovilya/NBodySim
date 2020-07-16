#ifndef TEXT_PANEL_H
#define TEXT_PANEL_H

#include <SFML/Graphics.hpp>

enum TextHorizontalAlign { LEFT, CENTER, RIGHT};

class TextPanel
{
private:
    sf::RectangleShape shape;

    sf::Text text;
    sf::Font* font;
public:
    TextPanel(sf::Vector2f position, sf::Vector2f size, char* text, sf::Font* font, int characterSize, TextHorizontalAlign align=TextHorizontalAlign::LEFT);
    void setText(char* text);
    void update();
    void render(sf::RenderTarget*);
};

#endif