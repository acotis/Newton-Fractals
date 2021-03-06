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
    // Current Fractal
    NewtonFractal *fractal;

    // Drawing components
    sf::Uint8 *pixels;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    // Dimensions
    int img_width;  // Dimensions of internal image
    int img_height;
    float display_shrink;
    int draw_height; // Height of finished part of image

    // Thread management
    std::thread *drawThread = nullptr;
    bool stopFlag = false; // Set to indicate that the current draw thread
    bool goFlag = false;    // Set to indicate that any previous draw thread has stopped and a new one can start

    // This method is private because FractalCanvas creates and manages a separate thread for it
    void drawFractal();
    void killDrawThread();

    void setDimensions(int _imq_width, int _img_height, float _display_shrink);

public:
    FractalCanvas(int _width, int _height, float _display_shrink);
    ~FractalCanvas();

    void drawNewFractal();
    void redrawFractal(int _width, int _height, float _display_shrink);
    void saveToPNG();

    void drawSelf(sf::RenderTarget &target);
};


#endif //NEWTONFRACTALS_FRACTALCANVAS_H
