//
// Created by evan on 9/10/17.
//

#include "FractalCanvas.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include <png++/rgb_pixel.hpp>
#include <png++/image.hpp>
#include <thread>


FractalCanvas::FractalCanvas(int _width, int _height, float _display_shrink) {
    img_width = _width;
    img_height = _height;
    pixels = nullptr;
    setPixelCount(img_width*img_height);

    display_shrink = _display_shrink;
    texture.setSmooth(true);
    sprite.setScale(sf::Vector2f(display_shrink, display_shrink));
}

FractalCanvas::~FractalCanvas() {
    delete pixels;
}


void FractalCanvas::setPixelCount(long count) {
    if(pixels != nullptr) {
        delete pixels;
    }
    pixels = new sf::Uint8[count*4];

}


void FractalCanvas::drawFractal(NewtonFractal *_fractal) {
    NewtonFractal *fractal = (NewtonFractal*) _fractal;

    float xstart = -FractalConstants::VIEW_WIDTH/2;
    float ystart = -FractalConstants::VIEW_HEIGHT/2;
    float xStep = FractalConstants::VIEW_WIDTH / img_width;
    float yStep = FractalConstants::VIEW_HEIGHT / img_height;

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

        if(stopFlag) {
            break;
        }
    }

    goFlag = true;
}


void FractalCanvas::drawNewFractal() {
    // Begin a new thread for drawing the fractal

    if(drawThread != nullptr) {
        stopFlag = true;
        while(!goFlag) {
            std::this_thread::__sleep_for(std::chrono::duration<int>(0), std::chrono::duration<int>(10000)); // 10 ms
        }
    }

    stopFlag = false;
    goFlag = false;

    drawThread = new std::thread(&FractalCanvas::drawFractal, this, new NewtonFractal);
}


void FractalCanvas::saveToPNG() {
    png::image<png::rgb_pixel> image(img_width, img_height);

    // Copy internal pixels onto the image

    for(int y=0; y<img_height; y++) {
        for(int x=0; x<img_width; x++) {
            // (Why can't this just be image.create(img_width, img_height, pixels)?)
            int ref = (y * img_width + x) * 4;
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
    image.create(img_width, img_height, pixels);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    target.draw(sprite);
}
