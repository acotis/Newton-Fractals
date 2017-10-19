//
// Created by evan on 10/13/17.
//

#ifndef NEWTONFRACTALS_RESOLUTIONPICKER_H
#define NEWTONFRACTALS_RESOLUTIONPICKER_H


#include "ClickablePanel.h"
#include "Button.h"

class ResolutionPicker : public ClickablePanel {
    static const int NBUTTONS;
    static const sf::IntRect ABUTTON_BOUNDS;
    static const sf::Color SELECT_COLOR;
    static const sf::Color UNSELECT_COLOR;
    static const sf::IntRect REQ_BOUNDS;

    std::vector<Button*> buttons;
    int selected = -1;

    void constructButtons();
    void selectButton(int nbutton);

public:
    ResolutionPicker(sf::Color _color);
    ResolutionPicker(sf::Color _color, sf::IntRect _absoluteBounds);
};


#endif //NEWTONFRACTALS_RESOLUTIONPICKER_H
