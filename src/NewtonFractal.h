//
// Created by evan on 8/30/17.
//

#ifndef NEWTONFRACTALS_NEWTONFRACTAL_H
#define NEWTONFRACTALS_NEWTONFRACTAL_H


#include "Typedefs.h"

class NewtonFractal {
    TransformFun transform;
    ColorFun colorFun;
    int infinity;

public:
    NewtonFractal();
    sf::Color getColorForStartLocation(float x, float y);
};


#endif //NEWTONFRACTALS_NEWTONFRACTAL_H
