
/*
 *  NEWTON FRACTALS
 *
 *  This program was written in ~Aug-Sep 2017 by Evan Rysdam.
 *  It is open source / public domain / free, but if you share the code, please:
 *     1. Don't claim you wrote it (ideally, just leave this notice in place).
 *     2. Don't claim I wrote any part that you added (that's probably illegal).
 *
 *  This code is provided AS-IS, with NO WARRANTY, explicit or implied.
 *  I am not responsible if it breaks anything when you run it.
 *  (But it shouldn't.)
 *
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include <png++/png.hpp>

#include "Constants.h"
#include "gui/Button.h"
#include "gui/FractalCanvas.h"
#include "gui/ClickablePanel.h"


int main() {
    srand(time(NULL));

    // Window and event
    sf::RenderWindow window(sf::VideoMode(FractalConstants::DISPLAY_WIDTH + 200, FractalConstants::DISPLAY_HEIGHT),
                            "Newton fractal");
    sf::Event nextEvent;

    FractalCanvas canvas(FractalConstants::IMG_WIDTH, FractalConstants::IMG_HEIGHT, FractalConstants::DISPLAY_SHRINK);

    // Controls
    ClickablePanel buttonPanel(
            sf::Color(10, 10, 0),
            sf::IntRect(FractalConstants::DISPLAY_WIDTH, 100, 200, 150));

    Button *drawRandomButton = new Button(sf::Color::Green, "Draw Random", std::bind(&FractalCanvas::drawNewFractal, &canvas));
    Button *saveToPNGButton = new Button(sf::Color::Cyan, "Save to PNG", std::bind(&FractalCanvas::saveToPNG, &canvas));
    buttonPanel.addClickable(drawRandomButton, sf::IntRect(50, 25, 100, 40));
    buttonPanel.addClickable(saveToPNGButton, sf::IntRect(50, 85, 100, 40));

    // Initial fractal
    canvas.drawNewFractal();

    while(window.isOpen()) {
        while(window.pollEvent(nextEvent)) {
            // Handle close events
            if(nextEvent.type == sf::Event::Closed) {
                window.close();
            }

            // Pass clicks onto the buttons
            if(nextEvent.type == sf::Event::MouseButtonPressed) {
                buttonPanel.handleClickAt(nextEvent.mouseButton.x, nextEvent.mouseButton.y);
            }
        }

        // Draw the image and buttons
        //std::cout << "Drawing image and buttons" << std::endl;
        canvas.drawSelf(window);

        window.draw(buttonPanel);

        window.display();
    }

    return 0;
}