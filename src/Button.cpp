//
// Created by evan on 9/4/17.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Button.h"


Button::Button(sf::IntRect _bounds, sf::Color _color, std::string _label, std::function<void(void)> _whenClicked) {
    bounds = _bounds;
    color = _color;
    label = _label;
    whenClicked = _whenClicked;

    outlineColor.r *= .8;
    outlineColor.g *= .8;
    outlineColor.b *= .8;

    sf::Font font;
    font.loadFromFile("Resources/DejaVuSans.ttf");
    text = sf::Text(label, font, 24);
    sf::FloatRect textBounds = text.getGlobalBounds();
    text.setOrigin(textBounds.width/2, textBounds.height/2);
    text.setPosition(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
    text.setColor(outlineColor);
}


void Button::drawSelf(sf::RenderTarget &target) {
    //std::cout << "Button::drawSelf(): begin" << std::endl;

    sf::RectangleShape box;
    box.setSize(sf::Vector2f(bounds.width-10, bounds.height-10));
    box.setPosition(bounds.left + 5, bounds.top + 5);
    box.setFillColor(color);
    box.setOutlineThickness(5);
    box.setOutlineColor(outlineColor);

    sf::FloatRect boxBounds = box.getGlobalBounds();
    //std::cout << "Drawing box(" <<  << ")";

    target.draw(box);

    //std::cout << "Button::drawSelf(): middle" << std::endl;

    //target.draw(text);

    //std::cout << "Button::drawSelf(): end" << std::endl;
}

bool Button::handleClickAt(float x, float y) {
    if(bounds.contains((int) x, (int) y)) {
        whenClicked();
        return true;
    } else {
        return false;
    }
}