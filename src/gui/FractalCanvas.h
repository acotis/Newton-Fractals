//
// Created by evan on 9/10/17.
//

#ifndef NEWTONFRACTALS_FRACTALCANVAS_H
#define NEWTONFRACTALS_FRACTALCANVAS_H


#include <SFML/Config.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <thread>
#include "../NewtonFractal.h"

class FractalCanvas {
    // Drawing components
    sf::Uint8 *pixels;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    // Dimensions
    int img_width;  // Dimensions of internal image
    int img_height;
    float display_shrink;

    // Thread management
    std::thread *drawThread = nullptr;
    bool stopFlag = false; // Set to indicate that the current draw thread
    bool goFlag = false;    // Set to indicate that any previous draw thread has stopped and a new one can start

    // This method is private because I want it to ALWAYS happen in a new thread
    // and therefore to just kill its own thread when it's done.
    // Obviously code like that can't go in a public method.
    void drawFractal(NewtonFractal *_fractal);

    void setPixelCount(long count);

public:
    FractalCanvas(int _width, int _height, float _display_shrink);
    ~FractalCanvas();

    void drawNewFractal();
    void saveToPNG();

    void drawSelf(sf::RenderTarget &target);
};


#endif //NEWTONFRACTALS_FRACTALCANVAS_H
