//
// Created by evan on 8/30/17.
//

#include "NewtonFractal.h"


NewtonFractal::NewtonFractal() {
    infinity = 20;

    transform = [](Complex z) {
        Complex num = z*z*z - 1.0f;
        Complex den = 3.0f*z*z;
        return new Complex(z - num/den);
    };

    colorFun = [this](std::complex<float> z, int iterations) {
        Complex a(1, 0);
        Complex b(-.5f, -.866f);
        Complex c(-.5f, .866f);

        sf::Color color;
        bool finished = true;

        float limit = .01;

        float greyF = 1 - (iterations + .0f) / infinity;
        greyF = std::pow(greyF, 1.0f);
        sf::Uint8 grey = (sf::Uint8) (255 * greyF);

        if (std::abs(z - a) < limit) color = sf::Color(grey, 0, 0);
        else if (std::abs(z - b) < limit) color = sf::Color(0, grey, 0);
        else if (std::abs(z - c) < limit) color = sf::Color(0, 0, grey);
        else {
            color = sf::Color(0, 0, 0);
            finished = false; // Keep going only if not near a root
        }

        return new MaybeColor(color, finished);
    };
};


sf::Color NewtonFractal::getColorForStartLocation(float x, float y) {
    std::complex<float> z(x, y);
    MaybeColor result;

    int iterations = 0;

    while(true) {
        result = *colorFun(z, iterations);

        if(result.second || iterations==infinity) {
            return result.first;
        }

        z = *transform(z);
        iterations++;
    }
}
