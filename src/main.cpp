#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>
#include <functional>

#include <pthread.h>

#include "Typedefs.h"
#include "NewtonFractal.h"
#include "Constants.h"


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
    srand(time(NULL));

    // (Image is drawn at half size)
    sf::RenderWindow window(sf::VideoMode(FractalConstants::DISPLAY_WIDTH, FractalConstants::DISPLAY_HEIGHT), "Newton fractal");
    sf::Event nextEvent;

    sf::Uint8 *pixels = new sf::Uint8[FractalConstants::IMG_WIDTH * FractalConstants::IMG_WIDTH * 4]; // Four bytes for each pixel (RGBA)
    sf::Image fractalImage;

    sf::Texture fractalTexture;
    fractalTexture.setSmooth(true);
    sf::Sprite fractalSprite;

    DrawFractalInfo info;
    info._fractal = new NewtonFractal;
    info._pixels = pixels;
    info._width = FractalConstants::IMG_WIDTH;
    info._height = FractalConstants::IMG_HEIGHT;
    info._viewFrame = sf::FloatRect(-FractalConstants::VIEW_WIDTH/2.0f, -FractalConstants::VIEW_HEIGHT/2.0f,
                                    FractalConstants::VIEW_WIDTH, FractalConstants::VIEW_HEIGHT);

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

        // Reload the pixels into the texture
        fractalImage.create(FractalConstants::IMG_WIDTH, FractalConstants::IMG_HEIGHT, pixels);
        fractalTexture.loadFromImage(fractalImage);
        fractalSprite.setTexture(fractalTexture, true);
        fractalSprite.setScale(FractalConstants::DISPLAY_SHRINK, FractalConstants::DISPLAY_SHRINK);

        // Draw the pixels
        window.draw(fractalSprite);
        window.display();
    }

    std::cout << "Outside of loop now." << std::endl;

    return 0;
}