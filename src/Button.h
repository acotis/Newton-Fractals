//
// Created by evan on 9/4/17.
//

#ifndef NEWTONFRACTALS_BUTTON_H
#define NEWTONFRACTALS_BUTTON_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

class Button : public sf::Drawable {
    // Primary attributes
    sf::IntRect bounds;
    sf::Color color;
    std::string label;
    std::function<void(void)> whenClicked;

    // Secondary attributes
    sf::Color outlineColor;
    sf::Color textColor;

    // sf components
    sf::RectangleShape box;
    sf::Text text;

public:
    Button(sf::IntRect _bounds, sf::Color _color, std::string _label, std::function<void(void)> _whenClicked);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool handleClickAt(float x, float y);
};


#endif //NEWTONFRACTALS_BUTTON_H
