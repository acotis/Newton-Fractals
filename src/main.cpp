
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
#include <complex>
#include <functional>
#include <png++/png.hpp>

#include <pthread.h>

#include "Typedefs.h"
#include "NewtonFractal.h"
#include "Constants.h"
#include "Button.h"


void saveImage() {
    png::image<png::rgb_pixel> image(FractalConstants::IMG_WIDTH, FractalConstants::IMG_HEIGHT);

    for(int y=0; y<FractalConstants::IMG_HEIGHT; y++) {
        for(int x=0; x<FractalConstants::IMG_WIDTH; x++) {
            int ref = (y * FractalConstants::IMG_WIDTH + x) * 4;
            image[y][x] = png::rgb_pixel(FractalConstants::PIXELS[ref],
                                         FractalConstants::PIXELS[ref+1],
                                         FractalConstants::PIXELS[ref+2]);
        }
    }

    int i=1;
    std::string filename;

    while(true) {
        filename = std::to_string(i);
        while(filename.length() < 3) filename = "0" + filename;

        filename = "output/fractal" + filename + ".png";

        if(!std::ifstream(filename)) {
            break;
        }

        i++;
    }

    image.write(filename);
    std::cout << "Image saved as " << filename << "." << std::endl;
}

void *drawFractal(void *_info) {
    // Draw the portion of the fractal inside bounds onto the image

    // Extract loop data and delete wrapper
    DrawFractalInfo *info = (DrawFractalInfo*) _info;
    NewtonFractal *fractal = info->_fractal;
    sf::Uint8 *pixels = info->_pixels;
    delete info;

    float xstart = -FractalConstants::VIEW_WIDTH/2;
    float ystart = -FractalConstants::VIEW_HEIGHT/2;
    float xStep = FractalConstants::VIEW_WIDTH / FractalConstants::IMG_WIDTH;
    float yStep = FractalConstants::VIEW_HEIGHT / FractalConstants::IMG_HEIGHT;

    // Loop and draw
    for(int yPix=0; yPix<FractalConstants::IMG_HEIGHT; yPix++) {
        for(int xPix=0; xPix<FractalConstants::IMG_WIDTH; xPix++) {
            float x = xstart + xPix * xStep;
            float y = ystart + yPix * yStep;

            sf::Color color = fractal->getColorForStartLocation(x, y);

            int offset = (yPix*FractalConstants::IMG_WIDTH + xPix) * 4;
            pixels[offset] = color.r;
            pixels[offset + 1] = color.g;
            pixels[offset + 2] = color.b;
            pixels[offset + 3] = color.a;
        }
    }

    // Kill thread
    pthread_detach(pthread_self());
}

void drawNewFractal() {
    // Begin a new thread for drawing the fractal

    DrawFractalInfo *info = new DrawFractalInfo;
    info->_fractal = new NewtonFractal;
    info->_pixels = FractalConstants::PIXELS;

    pthread_t drawFractalThread;
    pthread_create(&drawFractalThread, NULL, drawFractal, info);
}


int main() {
    srand(time(NULL));

    // Window and event
    sf::RenderWindow window(sf::VideoMode(FractalConstants::DISPLAY_WIDTH, FractalConstants::DISPLAY_HEIGHT + 100), "Newton fractal");
    sf::Event nextEvent;

    // Fractal-drawing stuff
    sf::Image fractalImage;
    sf::Texture fractalTexture;
    fractalTexture.setSmooth(true);
    sf::Sprite fractalSprite;

    // Controls
    Button buttons[] = {
            Button(sf::IntRect(250, 480, 140, 40), sf::Color::Cyan, "New fractal", drawNewFractal),
            Button(sf::IntRect(430, 480, 140, 40), sf::Color::Green, "Save fractal", saveImage),
    };
    int buttonCount = 2;

    drawNewFractal();

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

        // Reload the pixels into the texture
        fractalImage.create(FractalConstants::IMG_WIDTH, FractalConstants::IMG_HEIGHT, FractalConstants::PIXELS);
        fractalTexture.loadFromImage(fractalImage);
        fractalSprite.setTexture(fractalTexture, true);
        fractalSprite.setScale(FractalConstants::DISPLAY_SHRINK, FractalConstants::DISPLAY_SHRINK);

        // Draw the image and buttons
        //std::cout << "Drawing image and buttons" << std::endl;
        window.draw(fractalSprite);

        for(int i=0; i<buttonCount; i++) {
            buttons[i].drawSelf(window);
        }

        window.display();
    }

    return 0;
}