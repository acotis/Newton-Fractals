//
// Created by evan on 10/13/17.
//

#include "ResolutionPicker.h"


const int ResolutionPicker::NBUTTONS = 4;
const sf::IntRect ResolutionPicker::ABUTTON_BOUNDS = sf::IntRect(15, 15, 62, 40);
const sf::Color ResolutionPicker::SELECT_COLOR = sf::Color(180, 90, 0);
const sf::Color ResolutionPicker::UNSELECT_COLOR = sf::Color(250, 125, 0);
const sf::IntRect ResolutionPicker::REQ_BOUNDS = sf::IntRect(
        0,
        0,
        ABUTTON_BOUNDS.width*2 + ABUTTON_BOUNDS.left*3,
        ABUTTON_BOUNDS.height*((NBUTTONS+1)/2) + ABUTTON_BOUNDS.top*((NBUTTONS+3)/2));

ResolutionPicker::ResolutionPicker(sf::Color _color) : ClickablePanel(_color, REQ_BOUNDS) {
    constructButtons();
}


void ResolutionPicker::constructButtons() {
    sf::IntRect nextBounds = ABUTTON_BOUNDS;

    for(int i=0; i<NBUTTONS; i++) {
        if(i%2 == 1) {
            nextBounds.left += ABUTTON_BOUNDS.left + ABUTTON_BOUNDS.width;
        }

        Button *nextButton = new Button(UNSELECT_COLOR, "", std::bind(&ResolutionPicker::selectButton, this, i));
        buttons.push_back(nextButton);
        addClickable(nextButton, nextBounds);

        if(i%2 == 1) {
            nextBounds.left -= ABUTTON_BOUNDS.left + ABUTTON_BOUNDS.width;
            nextBounds.top += ABUTTON_BOUNDS.top + ABUTTON_BOUNDS.height;
        }
    }

    buttons[0]->setLabel("LQ");
    buttons[1]->setLabel("HQ");
    buttons[2]->setLabel("HD");
    buttons[3]->setLabel("4k");

    selectButton(0);
}

void ResolutionPicker::selectButton(int nbutton) {
    for(int i=0; i<NBUTTONS; i++) {
        buttons[i]->setColor(UNSELECT_COLOR);
    }
    buttons[nbutton]->setColor(SELECT_COLOR);
}