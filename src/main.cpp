#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>
#include <functional>

#include <pthread.h>

#include "Typedefs.h"
#include "NewtonFractal.h"


void *drawFractal(void *_info) {
    // Draw the portion of the fractal inside bounds onto the image

    // Extract loop data
    DrawFractalInfo *info = (DrawFractalInfo*) _info;

    NewtonFractal *fractal = info->_fractal;
    sf::Uint8 *pixels = info->_pixels;
    int width = info->_width;
    int height = info->_height;
    sf::FloatRect bounds = info->_viewFrame;

    float xStep = bounds.width / width;
    float yStep = bounds.height / height;

    // Loop and draw
    for(int yPix=0; yPix<height; yPix++) {
        for(int xPix=0; xPix<width; xPix++) {
            float x = bounds.left + xPix * xStep;
            float y = bounds.top + yPix * yStep;

            sf::Color color = fractal->getColorForStartLocation(x, y);

            int offset = (yPix*width + xPix) * 4;
            pixels[offset] = color.r;
            pixels[offset + 1] = color.g;
            pixels[offset + 2] = color.b;
            pixels[offset + 3] = color.a;
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Newton fractal");
    sf::Event nextEvent;

    sf::Uint8 *pixels = new sf::Uint8[800 * 600 * 4]; // Four bytes for each pixel (RGBA)
    sf::Image fractalImage;

    sf::Texture fractalTexture;
    fractalTexture.setSmooth(true);
    sf::Sprite fractalSprite;

    DrawFractalInfo info;
    info._fractal = new NewtonFractal;
    info._pixels = pixels;
    info._width = 800;
    info._height = 600;
    info._viewFrame = sf::FloatRect(-2.4f, -1.8f, 4.8, 3.6);

    //drawFractal(&info);

    pthread_t drawFractalThread;
    pthread_create(&drawFractalThread,
                   NULL,
                   drawFractal,
                   &info);

    while(window.isOpen()) {
        while(window.pollEvent(nextEvent)) {
            if(nextEvent.type == sf::Event::Closed) {
                std::cout << "Exiting game loop...";
                window.close();
            }
        }

        // Reload the pixels onto the screen
        fractalImage.create(800, 600, pixels);
        fractalTexture.loadFromImage(fractalImage);
        fractalSprite.setTexture(fractalTexture, true);

        // Draw the pixels
        window.draw(fractalSprite);
        window.display();
    }

    std::cout << "Outside of loop now." << std::endl;

    return 0;
}