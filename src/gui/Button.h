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
#include "Clickable.h"

class Button : public Clickable {
    // Primary attributes (includes absoluteBounds)
    sf::Color color;
    std::string label;
    std::function<void(void)> whenClicked;

    // Secondary attributes
    sf::Color outlineColor;
    sf::Color textColor;

    // sf components
    sf::Font *font;
    sf::RectangleShape box;
    sf::Text text;

    // Reload attributs
    void recomputeColors();
    void remakeSFComponents();

public:
    Button(sf::Color _color, std::string _label, std::function<void(void)> _whenClicked);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool handleClickAt(float x, float y);

    void setAbsoluteBounds(sf::IntRect _absoluteBounds);
    void setColor(sf::Color _color);
    void setLabel(std::string _text);
};


#endif //NEWTONFRACTALS_BUTTON_H
