//
// Created by evan on 10/13/17.
//

#ifndef NEWTONFRACTALS_BUTTONPANEL_H
#define NEWTONFRACTALS_BUTTONPANEL_H


#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Clickable.h"

class ClickablePanel : public Clickable {
    // Primary attributes
    sf::Color color;
    std::vector<Clickable*> clickables;

    // sf components
    sf::RectangleShape box;

public:
    ClickablePanel(sf::Color color);
    ClickablePanel(sf::Color, sf::IntRect _absoluteBounds);
    void addClickable(Clickable *clickable, sf::IntRect relativeBounds);
    bool handleClickAt(float x, float y);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    virtual sf::IntRect getAbsoluteBounds();
    virtual void setAbsoluteBounds(sf::IntRect _absoluteBounds);
};


#endif //NEWTONFRACTALS_BUTTONPANEL_H
