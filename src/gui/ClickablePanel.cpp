//
// Created by evan on 10/13/17.
//

#include "ClickablePanel.h"
#include <SFML/Graphics/RenderTarget.hpp>

ClickablePanel::ClickablePanel(sf::Color _color, sf::IntRect _absoluteBounds) {
    color = _color;
    setAbsoluteBounds(_absoluteBounds);
}

ClickablePanel::ClickablePanel(sf::Color _color) {
    ClickablePanel(_color, sf::IntRect(10, 10, 100, 100));
}


void ClickablePanel::addClickable(Clickable *clickable, sf::IntRect relativeBounds) {
    relativeBounds.left += absoluteBounds.left;
    relativeBounds.top += absoluteBounds.top;
    clickable->setAbsoluteBounds(relativeBounds);
    clickables.push_back(clickable);
}

bool ClickablePanel::handleClickAt(float x, float y) {
    for(auto nextClickable = clickables.begin(); nextClickable < clickables.end(); nextClickable++) {
        if((*nextClickable)->handleClickAt(x, y)) return true;
    }

    return false;
}

void ClickablePanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box, states);
    for(auto nextClickable = clickables.begin(); nextClickable < clickables.end(); nextClickable++) {
        target.draw(**nextClickable, states);
    }
}


sf::IntRect ClickablePanel::getAbsoluteBounds() {
    return absoluteBounds;
}

void ClickablePanel::setAbsoluteBounds(sf::IntRect _bounds) {
    int dx = _bounds.left - absoluteBounds.left;
    int dy = _bounds.top - absoluteBounds.top;

    absoluteBounds = _bounds;
    box = sf::RectangleShape(sf::Vector2f(absoluteBounds.width, absoluteBounds.height));
    box.setPosition(absoluteBounds.left, absoluteBounds.top);
    box.setFillColor(color);

    // Move children by same amount
    for(auto nextClickable = clickables.begin(); nextClickable < clickables.end(); nextClickable++) {
        sf::IntRect childBounds = (*nextClickable)->getAbsoluteBounds();
        childBounds.left += dx;
        childBounds.top += dy;
        (*nextClickable)->setAbsoluteBounds(childBounds);
    }
}