//
// Created by evan on 9/4/17.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Button.h"


Button::Button(sf::Color _color, std::string _label, std::function<void(void)> _whenClicked) {
    // Primary attributes
    color = _color;
    label = _label;
    whenClicked = _whenClicked;

    // font
    font = new sf::Font(); // Must create font on the heap so it isn't deleted when the constructor finishes
    font->loadFromFile("Resources/DejaVuSans.ttf");

    // Secondary attributes
    recomputeColors();

    setAbsoluteBounds(sf::IntRect(10, 10, 100, 100));
}


void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box, states);
    target.draw(text, states);
}

bool Button::handleClickAt(float x, float y) {
    if(absoluteBounds.contains((int) x, (int) y)) {
        whenClicked();
        return true;
    } else {
        return false;
    }
}


/* Setters and getters (and helpers thereof) */

void Button::recomputeColors() {
    // Secondary attributes
    outlineColor = color;
    outlineColor.r *= .8;
    outlineColor.g *= .8;
    outlineColor.b *= .8;

    textColor = color;
    textColor.r *= .1;
    textColor.g *= .1;
    textColor.b *= .1;

    remakeSFComponents();
}

void Button::remakeSFComponents() {
    // Re-set box to use new bounds
    box.setSize(sf::Vector2f(absoluteBounds.width-10, absoluteBounds.height-10));
    box.setPosition(absoluteBounds.left + 5, absoluteBounds.top + 5);
    box.setFillColor(color);
    box.setOutlineThickness(5);
    box.setOutlineColor(outlineColor);

    // Re-fit text to box
    text = sf::Text(label, *font, 18);
    sf::FloatRect textBounds = text.getGlobalBounds();
    text.setOrigin(textBounds.width/2, textBounds.height/2);
    text.setPosition(absoluteBounds.left + absoluteBounds.width/2, absoluteBounds.top + absoluteBounds.height/2 - 5); // Slightly non-general scaling
    text.setColor(textColor);
}

void Button::setAbsoluteBounds(sf::IntRect _absoluteBounds) {
    absoluteBounds = _absoluteBounds;
    remakeSFComponents();
}

void Button::setColor(sf::Color _color) {
    color = _color;
    recomputeColors();
}

void Button::setLabel(std::string _label) {
    label = _label;
    remakeSFComponents();
}