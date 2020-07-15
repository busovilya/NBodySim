#include "button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, sf::Text text, sf::Font* font, sf::Color idleColor, sf::Color pressedColor)
{
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(width, height));

    this->text = text;
    this->font = font;

    this->text.setFont(*font);
    this->text.setCharacterSize(14);
    this->text.setPosition(rect.getPosition().x + rect.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
                           rect.getPosition().y + rect.getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);

    this->idleColor = idleColor;
    this->pressedColor = pressedColor;

    state = ButtonStates::IDLE_BTN; 
    rect.setFillColor(idleColor);
};

void Button::render(sf::RenderTarget* target)
{
    target->draw(rect);
    target->draw(text);
};

void Button::update(sf::Vector2i mousePosition)
{
    if(rect.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(this->state == ButtonStates::IDLE_BTN)
                this->state = ButtonStates::PRESSED_BTN;
        }
        else
        {
            if(this->state == ButtonStates::PRESSED_BTN)
                this->state = ButtonStates::IDLE_BTN;
        }
        
    switch (this->state)
    {
        case ButtonStates::IDLE_BTN:
            this->rect.setFillColor(this->idleColor);
            break;
        case ButtonStates::PRESSED_BTN:
            this->rect.setFillColor(this->pressedColor);
            break;
    }
    }
};

Button::~Button()
{
};