//
// Created by evan on 8/30/17.
//

#include <deque>
#include <iostream>
#include "NewtonFractal.h"
#include "Constants.h"


const sf::Color NewtonFractal::ROOT_COLORS[] = {
        //sf::Color(255, 128, 0),
        //sf::Color(255, 80, 120),
        //sf::Color::Red, sf::Color::Blue,
        //sf::Color::Green, sf::Color::Yellow,
        //sf::Color::Cyan, sf::Color::Magenta, sf::Color::White,
        //sf::Color::Black,
        //sf::Color::Green,
        sf::Color::Red, sf::Color::Green, sf::Color::Blue,
        sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White,
        sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White,


//        sf::Color(0, 50, 255), sf::Color::Red, sf::Color::Green,
//    sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan,
//    sf::Color::White, sf::Color(255, 128, 0)
};


/* Internal polynomial functionality */

void NewtonFractal::computeDerivative() {
    std::deque<Complex> polynomialTerms;

    polynomialTerms.push_front(Complex(1, 0));

    // Calculate the actual terms of the polynomial by doing out the multiplication zero by zero
    for(auto nextZ = polynomialZeros.begin(); nextZ < polynomialZeros.end(); nextZ++) {
        polynomialTerms.push_front(Complex(0, 0));
        for(int i=0; i<polynomialTerms.size()-1; i++) {
            polynomialTerms[i] -= (*nextZ)*polynomialTerms[i+1];
        }
    }

    // Calculate the terms of the derivative
    // (If there is only one term (the constant term) of the polynomial, the derivative is zero)
    if(polynomialTerms.size() == 1) {
        derivativeTerms.push_back(Complex(0, 0));
    } else {
        for(int i=1; i<polynomialTerms.size(); i++) {
            derivativeTerms.push_back(polynomialTerms[i] * (float) i);
        }
    }

    // Print polynomial and derivative

    for(int i=0; i<polynomialTerms.size(); i++) {
        std::cout << polynomialTerms[i] << " ";
    }
    std::cout << std::endl;

    for(int i=0; i<derivativeTerms.size(); i++) {
        std::cout << derivativeTerms[i] << " ";
    }
    std::cout << std::endl;
}

Complex NewtonFractal::evaluatePolynomial(Complex input) {
    Complex resultAccum(1, 0); // Each zero's "contribution" is multiplied into here

    for(int i=0; i<polynomialZeros.size(); i++) {
        resultAccum *= (input - polynomialZeros[i]);
    }

    return resultAccum;
}

Complex NewtonFractal::evaluateDerivative(Complex input) {
    Complex inputPower(1, 0); // First 1, then input, then input^2, then input^3, etc
    Complex resultAccum(0, 0); // Each term adds to this

    for(int i=0; i<derivativeTerms.size(); i++) {
        resultAccum += inputPower*derivativeTerms[i];
        inputPower *= input;
    }

    return resultAccum;
}


/* Internal fractal functionality */

Complex* NewtonFractal::transform(Complex z) {
    //Complex num = z*z*z - 1.0f;
    //Complex den = 3.0f*z*z;
    Complex num = evaluatePolynomial(z);
    Complex den = evaluateDerivative(z);
    return new Complex(z - num/den);
}

MaybeColor* NewtonFractal::colorFun(Complex z, int iteration) {
    // If very close to a root, return the color associated with that root
    for(int i=0; i<polynomialZeros.size(); i++) {
        float dist = std::abs(z-polynomialZeros[i]);

        if(dist < .01) {
            // distAdjust should be 0 for dist = 0 and 1 for dist = .01
            // It should also make the images look nice and smooth
            float distAdjust = (float) (sqrt(dist)*10);
            float shade = ((iteration + distAdjust)/infinity) + .05f;
            shade = std::min(std::max(shade, 0.0f), 1.0f);

            sf::Color base = ROOT_COLORS[i];
            base.r *= shade;
            base.g *= shade;
            base.b *= shade;

            return new MaybeColor(base, true);
        }
    }

    // Else, return black/false
    return new MaybeColor(sf::Color::Black, false);
}


/* Public functionality */

NewtonFractal::NewtonFractal() {
    float scale = 5;
    for(int i=0; i<12; i++) {
        float x = (rand() / (RAND_MAX + .0f)) * FractalConstants::VIEW_WIDTH*scale - FractalConstants::VIEW_WIDTH*scale*.5f;
        float y = (rand() / (RAND_MAX + .0f)) * FractalConstants::VIEW_HEIGHT*scale - FractalConstants::VIEW_HEIGHT*scale*.5f;
        polynomialZeros.push_back(Complex(x, y));
        //polynomialZeros.push_back(Complex(x, y));
    }
    //polynomialZeros.push_back(Complex(0, 0));

    //polynomialZeros.push_back(Complex(-1.34308f, -.151646f));
    //polynomialZeros.push_back(Complex(-1.08480f, -1.59306f));
    //polynomialZeros.push_back(Complex(-.95964f, 1.78098f));
    //polynomialZeros.push_back(Complex(-.054242f, -1.398502f));
    //polynomialZeros.push_back(Complex(.236283f, 1.59648f));
    //polynomialZeros.push_back(Complex(.37351f, 1.47488f));

    computeDerivative();

    //Complex test(0, 1);
    //std::cout << "P(" << test << ") = " << evaluatePolynomial(test) << std::endl;
    //std::cout << "P'(" << test << ") = " << evaluateDerivative(test) << std::endl;

    infinity = 80; // ;-)
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
