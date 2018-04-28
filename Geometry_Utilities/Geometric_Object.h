//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_GEOMETRIC_OBJECT_H
#define C_RAYTRACER_GEOMETRIC_OBJECT_H

#include <iostream>
#include "../Math_Utilities/Vector.h"
#include "../Tracing_Utilities/Colour.h"
#include "../Tracing_Utilities/Ray.h"

using namespace std;

class Geometric_Object {
public:

    Geometric_Object();

    virtual Colour getColour();

    virtual Vector getNormalAt(Vector intersection_position);
    virtual double findIntersection(Ray ray);
};


#endif //C_RAYTRACER_GEOMETRIC_OBJECT_H
