#include "text_panel.h"


TextPanel::TextPanel(sf::Vector2f position, sf::Vector2f size, char* text, sf::Font* font, int characterSize, TextHorizontalAlign align)
{
    shape.setPosition(position);
    shape.setSize(size);

    this->text.setString(text);
    this->text.setFont(*font);
    this->text.setCharacterSize(characterSize);

    if(align == LEFT)
        this->text.setPosition(shape.getPosition().x + 10,
                            shape.getPosition().y + shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
    else if(align == CENTER)
        this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
                            shape.getPosition().y + shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
    else if(align == RIGHT)
        this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width - this->text.getGlobalBounds().width - 10,
                            shape.getPosition().y + shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);

    this->text.setFillColor(sf::Color::Black);
}

void TextPanel::setText(char* text)
{
    this->text.setString(text);
}

void TextPanel::render(sf::RenderTarget* target)
{
    target->draw(text);
}