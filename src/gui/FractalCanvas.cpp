//
// Created by evan on 9/10/17.
//

#include "FractalCanvas.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include <png++/rgb_pixel.hpp>
#include <png++/image.hpp>
#include <thread>


FractalCanvas::FractalCanvas(int _width, int _height, float _shrink_factor) {
    width = _width;
    height = _height;
    pixels = new sf::Uint8[width*height*4];

    shrink_factor = _shrink_factor;
    texture.setSmooth(true);
    sprite.setScale(sf::Vector2f(shrink_factor, shrink_factor));
}

FractalCanvas::~FractalCanvas() {
    delete pixels;
}


void FractalCanvas::drawFractal(NewtonFractal *_fractal) {
    NewtonFractal *fractal = (NewtonFractal*) _fractal;

    float xstart = -FractalConstants::VIEW_WIDTH/2;
    float ystart = -FractalConstants::VIEW_HEIGHT/2;
    float xStep = FractalConstants::VIEW_WIDTH / width;
    float yStep = FractalConstants::VIEW_HEIGHT / height;

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
}


void FractalCanvas::drawNewFractal() {
    // Begin a new thread for drawing the fractal

    std::thread *drawThread = new std::thread(&FractalCanvas::drawFractal, this, new NewtonFractal);
}


void FractalCanvas::saveToPNG() {
    png::image<png::rgb_pixel> image(width, height);

    // Copy internal pixels onto the image

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            int ref = (y * width + x) * 4;
            image[y][x] = png::rgb_pixel(pixels[ref], pixels[ref+1], pixels[ref+2]);
        }
    }

    // Find an unused filename of the form output/fractal*.png

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

    // Save the image

    image.write(filename);
    std::cout << "Image saved as " << filename << "." << std::endl;
}


void FractalCanvas::drawSelf(sf::RenderTarget &target) {
    image.create(width, height, pixels);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    target.draw(sprite);
}
