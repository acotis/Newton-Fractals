#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>
#include <functional>
#include <png++/png.hpp>

#include <pthread.h>

#include "Typedefs.h"
#include "NewtonFractal.h"
#include "Constants.h"


void saveImageAs(std::string name, sf::Uint8 *pixels) {
    std::cout << "Creating image..." << std::endl;

    png::image<png::rgb_pixel> image(FractalConstants::IMG_WIDTH, FractalConstants::IMG_HEIGHT);

    std::cout << "Done.  Writing pixels onto the image..." << std::endl;

    for(int y=0; y<FractalConstants::IMG_HEIGHT; y++) {
        //std::cout << "y = " << y << std::endl;
        for(int x=0; x<FractalConstants::IMG_WIDTH; x++) {
            //std::cout << "  x = " << x << std::endl;
            int ref = (y * FractalConstants::IMG_WIDTH + x) * 4;
            //image[y][x] = png::rgb_pixel(0, 0, 0);
            image[y][x] = png::rgb_pixel(pixels[ref], pixels[ref+1], pixels[ref+2]);
        }
    }

    std::cout << "Done.  Writing image to disk..." << std::endl;

    image.write(name);

    std::cout << "Done." << std::endl;
}


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

    // Save image
    saveImageAs("output.png", pixels);
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

    // TODO: remove width and height info from the DrawFractalInfo thing
    DrawFractalInfo info;
    info._fractal = new NewtonFractal;
    info._pixels = pixels;
    info._width = FractalConstants::IMG_WIDTH;
    info._height = FractalConstants::IMG_HEIGHT;
    info._viewFrame = sf::FloatRect(-FractalConstants::VIEW_WIDTH/2.0f, -FractalConstants::VIEW_HEIGHT/2.0f,
                                    FractalConstants::VIEW_WIDTH, FractalConstants::VIEW_HEIGHT);

    // Begin a new thread for drawing the fractal
    pthread_t drawFractalThread;
    pthread_create(&drawFractalThread, NULL, drawFractal, &info);

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