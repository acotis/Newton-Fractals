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
    pixels = nullptr;
    setDimensions(_width, _height, _display_shrink);

    texture.setSmooth(true);
}

FractalCanvas::~FractalCanvas() {
    delete pixels;
}


void FractalCanvas::setDimensions(int _img_width, int _img_height, float _display_shrink) {
    std::cout << std::endl << "FractalCanvas::setDimensions(" << _img_width << ", " << _img_height << ", " << _display_shrink << ")" << std::endl;

    img_width = _img_width;
    img_height = _img_height;
    display_shrink = _display_shrink;

    if(pixels != nullptr) {
        delete pixels;
    }
    pixels = new sf::Uint8[img_width*img_height*4];

    image.create(img_width, img_height, pixels);
    sf::Vector2u imgSize = image.getSize();
    std::cout << "imgSize.x = " << imgSize.x;

    std::cout << "  sprite.getScale().x = " << sprite.getScale().x << std::endl;
}


void FractalCanvas::drawFractal() {
    float xstart = -FractalConstants::VIEW_WIDTH/2;
    float ystart = -FractalConstants::VIEW_HEIGHT/2;
    float xStep = FractalConstants::VIEW_WIDTH / img_width;
    float yStep = FractalConstants::VIEW_HEIGHT / img_height;

    std::cout << "img_width = " << img_width << std::endl;

    for(int yPix=0; yPix<img_height; yPix++) {
        for(int xPix=0; xPix<img_width; xPix++) {
            int offset = (yPix*img_width + xPix) * 4;
            pixels[offset] = 0;
            pixels[offset + 1] = 0;
            pixels[offset + 2] = 0;
            pixels[offset + 3] = 0;
        }
    }

    // Loop and draw
    for(int yPix=0; yPix<img_height; yPix++) {
        // Draw a red line ahead of the drawing
        for(int yplus = 1; yPix+yplus<img_height && yplus < 2; yplus++) {
            for (int xPix = 0; xPix < img_width; xPix++) {
                int offset = ((yPix + yplus) * img_width + xPix) * 4;
                pixels[offset] = 255;
                pixels[offset + 1] = 0;
                pixels[offset + 2] = 0;
                pixels[offset + 3] = 255;
            }
        }

        for(int xPix=0; xPix<img_width; xPix++) {
            float x = xstart + xPix * xStep;
            float y = ystart + yPix * yStep;

            sf::Color color = fractal->getColorForStartLocation(x, y);

            int offset = (yPix*img_width + xPix) * 4;
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


void FractalCanvas::killDrawThread() {
    if(drawThread != nullptr) {
        stopFlag = true;
        while(!goFlag) {
            std::this_thread::__sleep_for(std::chrono::duration<int>(0), std::chrono::duration<int>(10000)); // 10 ms
        }
    }

    stopFlag = false;
    goFlag = false;
}


void FractalCanvas::redrawFractal(int _width, int _height, float _display_shrink) {
    killDrawThread();

    setDimensions(_width, _height, _display_shrink);

    if(fractal == nullptr) return; // If there's no fractal to draw, don't try to draw it

    drawThread = new std::thread(&FractalCanvas::drawFractal, this);
}


void FractalCanvas::drawNewFractal() {
    killDrawThread();
    fractal = new NewtonFractal;
    drawThread = new std::thread(&FractalCanvas::drawFractal, this);
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
    sprite.setTexture(texture, true);
    sprite.setScale(sf::Vector2f(display_shrink, display_shrink));

    std::cout << std::endl;
    std::cout << "image width   = " << image.getSize().x << std::endl;
    std::cout << "texture width = " << texture.getSize().x << std::endl;
    std::cout << "sprite width  = " << sprite.getGlobalBounds().width << std::endl;

    target.draw(sprite);
}
