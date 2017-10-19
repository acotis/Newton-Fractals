
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
#include "gui/ResolutionPicker.h"


FractalCanvas fractalCanvas(FractalConstants::IMG_WIDTHS[1], FractalConstants::IMG_HEIGHTS[1], FractalConstants::DISPLAY_SHRINKS[1]);

namespace ControlCenter {
    void setFractalCanvasResolution(int resolutionID) {
        fractalCanvas.redrawFractal(
                FractalConstants::IMG_WIDTHS[resolutionID],
                FractalConstants::IMG_HEIGHTS[resolutionID],
                FractalConstants::DISPLAY_SHRINKS[resolutionID]);
    }
}


int main() {
    srand(time(NULL));

    // Window and event
    sf::RenderWindow window(
            sf::VideoMode(FractalConstants::DISPLAY_WIDTH + 200, FractalConstants::DISPLAY_HEIGHT),
            "Newton fractal");
    sf::Event nextEvent;

    std::cout << "Creating controls..." << std::endl;

    // Controls
    ClickablePanel controlPanel(
            sf::Color(180, 200, 200),
            sf::IntRect(FractalConstants::DISPLAY_WIDTH, 0, 200, FractalConstants::DISPLAY_HEIGHT));

    // Generate panel
    ClickablePanel *generatePanel = new ClickablePanel(sf::Color(120, 140, 140));
    Button *generateButton = new Button(sf::Color::Green, "Generate", std::bind(&FractalCanvas::drawNewFractal, &fractalCanvas));
    generatePanel->addClickable(generateButton, sf::IntRect(15, 15, 140, 40));

    // Resolution panel
    ResolutionPicker *resolutionPicker = new ResolutionPicker(sf::Color(120, 140, 140));
    int resPickWidth = resolutionPicker->getAbsoluteBounds().width;
    int resPickHeight = resolutionPicker->getAbsoluteBounds().height;

    // Save panel
    ClickablePanel *savePanel = new ClickablePanel(sf::Color(120, 140, 140));
    Button *saveToPNGButton = new Button(sf::Color::Cyan, "Save to PNG", std::bind(&FractalCanvas::saveToPNG, &fractalCanvas));
    savePanel->addClickable(saveToPNGButton, sf::IntRect(15, 15, 140, 40));


    // Add stuff to control panel
    controlPanel.addClickable(generatePanel, sf::IntRect(15, 15, 170, 70));
    controlPanel.addClickable(resolutionPicker, sf::IntRect(15, 100, resPickWidth, resPickHeight));
    controlPanel.addClickable(savePanel, sf::IntRect(15, 100 + resPickHeight + 15, 170, 70));

    std::cout << "Drawing initial fractal..." << std::endl;

    // Initial fractal
    fractalCanvas.drawNewFractal();

    while(window.isOpen()) {
        while(window.pollEvent(nextEvent)) {
            // Handle close events
            if(nextEvent.type == sf::Event::Closed) {
                window.close();
            }

            // Pass clicks onto the buttons
            if(nextEvent.type == sf::Event::MouseButtonPressed) {
                controlPanel.handleClickAt(nextEvent.mouseButton.x, nextEvent.mouseButton.y);
            }
        }

        // Draw the image and buttons
        fractalCanvas.drawSelf(window);
        window.draw(controlPanel);
        window.display();
    }

    return 0;
}