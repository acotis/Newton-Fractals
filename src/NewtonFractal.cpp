//
// Created by evan on 8/30/17.
//

#include <deque>
#include <iostream>
#include <stdfix.h>
#include "NewtonFractal.h"


/* Internal functionality */

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
        derivativTerms.push_back(Complex(0, 0));
    } else {
        for(int i=1; i<polynomialTerms.size(); i++) {
            derivativTerms.push_back(polynomialTerms[i] * (float) i);
        }
    }

    // Print polynomial and derivative

    for(int i=0; i<polynomialTerms.size(); i++) {
        std::cout << polynomialTerms[i] << " ";
    }
    std::cout << std::endl;

    for(int i=0; i<derivativTerms.size(); i++) {
        std::cout << derivativTerms[i] << " ";
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

    for(int i=0; i<derivativTerms.size(); i++) {
        resultAccum += inputPower*derivativTerms[i];
        inputPower *= input;
    }

    return resultAccum;
}


/* Public functionality */


NewtonFractal::NewtonFractal() {
    polynomialZeros.push_back(Complex(1, 0));
    polynomialZeros.push_back(Complex(-.5f, 0));
    polynomialZeros.push_back(Complex(0, 1));

    computeDerivative();

    //Complex test(0, 1);
    //std::cout << "P(" << test << ") = " << evaluatePolynomial(test) << std::endl;
    //std::cout << "P'(" << test << ") = " << evaluateDerivative(test) << std::endl;

    infinity = 20; // ;-)

    transform = [this](Complex z) {
        //Complex num = z*z*z - 1.0f;
        //Complex den = 3.0f*z*z;
        Complex num = evaluatePolynomial(z);
        Complex den = evaluateDerivative(z);
        return new Complex(z - num/den);
    };

    colorFun = [this](std::complex<float> z, int iterations) {
        Complex a = polynomialZeros[0];
        Complex b = polynomialZeros[1];
        Complex c = polynomialZeros[2];

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
