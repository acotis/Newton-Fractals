
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
#include "Button.h"
#include "FractalCanvas.h"


int main() {
    srand(time(NULL));

    // Window and event
    sf::RenderWindow window(sf::VideoMode(FractalConstants::DISPLAY_WIDTH, FractalConstants::DISPLAY_HEIGHT + 100), "Newton fractal");
    sf::Event nextEvent;

    FractalCanvas canvas(FractalConstants::IMG_WIDTH, FractalConstants::IMG_HEIGHT, FractalConstants::DISPLAY_SHRINK);

    // Controls
    Button buttons[] = {
            Button(sf::IntRect(250, 480, 140, 40), sf::Color::Cyan, "New",
                    std::bind(&FractalCanvas::drawNewFractal, &canvas)),

            Button(sf::IntRect(430, 480, 140, 40), sf::Color::Green, "Save",
                    std::bind(&FractalCanvas::saveToPNG, &canvas)),
    };
    int buttonCount = 2;

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
                for(int i=0; i<buttonCount; i++) {
                    if(buttons[i].handleClickAt(nextEvent.mouseButton.x, nextEvent.mouseButton.y)) {
                        break;
                    }
                }
            }
        }

        // Draw the image and buttons
        //std::cout << "Drawing image and buttons" << std::endl;
        canvas.drawSelf(window);

        for(int i=0; i<buttonCount; i++) {
            buttons[i].drawSelf(window);
        }

        window.display();
    }

    return 0;
}