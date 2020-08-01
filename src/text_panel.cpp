#include "text_panel.h"


TextPanel::TextPanel(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font* font, int characterSize, sf::Color textColor, TextHorizontalAlign align)
{
    shape.setPosition(position);
    shape.setSize(size);

    this->text.setString(text);
    this->text.setFont(*font);
    this->text.setCharacterSize(characterSize);
    this->text.setFillColor(textColor);

    if(align == LEFT)
        this->text.setPosition(shape.getPosition().x + 10,
                            shape.getPosition().y + shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
    else if(align == CENTER)
        this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
                            shape.getPosition().y + shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
    else if(align == RIGHT)
        this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width - this->text.getGlobalBounds().width - 10,
                            shape.getPosition().y + shape.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);

}

void TextPanel::update(std::string text)
{
    this->text.setString(text);
}

void TextPanel::render(sf::RenderTarget* target)
{
    target->draw(text);
}