//
// Created by wesse on 2018/04/05.
//

#ifndef C_RAYTRACER_LIGHT_SOURCE_H
#define C_RAYTRACER_LIGHT_SOURCE_H

#include <iostream>
#include "Colour.h"
#include "../Math_Utilities/Vector.h"

using namespace std;

class Light_Source {
public:
    Light_Source();

    virtual Vector getLightPosition();
    virtual Colour getLightColour();
};


#endif //C_RAYTRACER_LIGHT_SOURCE_H
