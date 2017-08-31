//
// Created by evan on 8/30/17.
//

#ifndef NEWTONFRACTALS_NEWTONFRACTAL_H
#define NEWTONFRACTALS_NEWTONFRACTAL_H


#include "Typedefs.h"

class NewtonFractal {
    static const sf::Color ROOT_COLORS[];

    std::vector<Complex> polynomialZeros;
    std::vector<Complex> derivativeTerms;    // Element N is x^N term (i.e. 0th element is constant term)

    TransformFun transform;
    ColorFun colorFun;
    int infinity;

    void computeDerivative();
    Complex evaluatePolynomial(Complex input);
    Complex evaluateDerivative(Complex input);

public:
    NewtonFractal();
    sf::Color getColorForStartLocation(float x, float y);
};


#endif //NEWTONFRACTALS_NEWTONFRACTAL_H
