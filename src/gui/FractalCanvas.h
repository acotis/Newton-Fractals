//
// Created by evan on 9/10/17.
//

#ifndef NEWTONFRACTALS_FRACTALCANVAS_H
#define NEWTONFRACTALS_FRACTALCANVAS_H


#include <SFML/Config.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../NewtonFractal.h"

class FractalCanvas {
    sf::Uint8 *pixels;

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    // These dimensions refer to the INTERNAL PIXEL COUNT.
    // This is also the size that the image will be saved at.
    int width;
    int height;

    // Shrink factor refers to how much smaller the display is than the image.
    // (Use values > 1 for pixelated display)
    float shrink_factor;

    // This method is private because I want it to ALWAYS happen in a new thread
    // and therefore to just kill its own thread when it's done.
    // Obviously code like that can't go in a public method.
    void drawFractal(NewtonFractal *_fractal);

public:
    FractalCanvas(int _width, int _height, float _shrink_factor);
    ~FractalCanvas();

    void drawNewFractal();
    void saveToPNG();

    void drawSelf(sf::RenderTarget &target);
};


#endif //NEWTONFRACTALS_FRACTALCANVAS_H
