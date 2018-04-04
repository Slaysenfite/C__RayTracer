//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_LIGHT_H
#define C_RAYTRACER_LIGHT_H

#include <iostream>
#include "Vector.h"
#include "Colour.h"

using namespace std;

class Light {

public:
    Light();
    Light(Vector pos, Colour col);

    virtual Vector &getPosition();
    virtual Colour &getColour();

private:
    Vector position;
    Colour colour;
};


#endif //C_RAYTRACER_LIGHT_H
