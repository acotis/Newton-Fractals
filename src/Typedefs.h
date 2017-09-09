//
// Created by evan on 8/30/17.
//

#ifndef NEWTONFRACTALS_TYPEDEFS_H
#define NEWTONFRACTALS_TYPEDEFS_H

#include <functional>
#include <complex>
#include <SFML/Graphics.hpp>

typedef std::pair<sf::Color,bool> MaybeColor;
typedef std::complex<float> Complex;
typedef std::function<Complex*(Complex)> TransformFun;
typedef std::function<MaybeColor*(Complex, int)> ColorFun;

class NewtonFractal;

struct DrawFractalInfo {
    NewtonFractal *_fractal;
    sf::Uint8 *_pixels;
};

#endif //NEWTONFRACTALS_TYPEDEFS_H
