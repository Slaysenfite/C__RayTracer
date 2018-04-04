//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_SPHERE_H
#define C_RAYTRACER_SPHERE_H

#include <iostream>
#include "Vector.h"
#include "Colour.h"
#include "Geometric_Object.h"

using namespace std;

class Sphere : public Geometric_Object {
public:
    Sphere();
    Sphere(Vector v, double r, Colour c);

    Vector getCenter();
    double getRadius();
    virtual Colour getColour();

private:
    Vector center;
    double  radius;
    Colour colour;
};


#endif //C_RAYTRACER_SPHERE_H
