//
// Created by evan on 8/30/17.
//

#ifndef NEWTONFRACTALS_NEWTONFRACTAL_H
#define NEWTONFRACTALS_NEWTONFRACTAL_H


#include "Typedefs.h"

class NewtonFractal {
    static const sf::Color ROOT_COLORS[];

    std::vector<Complex> polynomialZeros;
    std::vector<Complex> derivativeTerms;   // Element N is x^N term (i.e. 0th element is constant term)

    //TransformFun transform;
    //ColorFun colorFun;
    int infinity;

    // Polynomial functionality
    void computeDerivative(); // Used in constructor
    Complex evaluatePolynomial(Complex input);
    Complex evaluateDerivative(Complex input);

    // Fractal functionality
    Complex* transform(Complex z); // z -> [z - P(z)/P'(z)]
    MaybeColor* colorFun(Complex z, int iteration);

public:
    NewtonFractal();
    sf::Color getColorForStartLocation(float x, float y);
};


#endif //NEWTONFRACTALS_NEWTONFRACTAL_H
