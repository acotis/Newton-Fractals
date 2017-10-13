//
// Created by evan on 9/4/17.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Button.h"


Button::Button(sf::IntRect _bounds, sf::Color _color, std::string _label, std::function<void(void)> _whenClicked) {
    // Primary attributes
    bounds = _bounds;
    color = _color;
    label = _label;
    whenClicked = _whenClicked;

    // Secondary attributes
    outlineColor = color;
    outlineColor.r *= .8;
    outlineColor.g *= .8;
    outlineColor.b *= .8;

    textColor = color;
    textColor.r *= .1;
    textColor.g *= .1;
    textColor.b *= .1;

    // sf components
    box.setSize(sf::Vector2f(bounds.width-10, bounds.height-10));
    box.setPosition(bounds.left + 5, bounds.top + 5);
    box.setFillColor(color);
    box.setOutlineThickness(5);
    box.setOutlineColor(outlineColor);

    sf::Font *font = new sf::Font(); // Must create font on the heap so it isn't deleted when the constructor finishes
    font->loadFromFile("Resources/DejaVuSans.ttf");
    text = sf::Text(label, *font, 24);
    sf::FloatRect textBounds = text.getGlobalBounds();
    text.setOrigin(textBounds.width/2, textBounds.height/2);
    text.setPosition(bounds.left + bounds.width/2, bounds.top + bounds.height/2 - 5); // Slightly non-general scaling
    //text.scale(sf::Vector2f(.8f, .8f));
    text.setColor(textColor);
}


void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box, states);
    target.draw(text, states);
}

bool Button::handleClickAt(float x, float y) {
    if(bounds.contains((int) x, (int) y)) {
        whenClicked();
        return true;
    } else {
        return false;
    }
}