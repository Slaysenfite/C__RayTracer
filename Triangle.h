//
// Created by wesse on 2018/04/05.
//

#ifndef C_RAYTRACER_TRIANGLE_H
#define C_RAYTRACER_TRIANGLE_H

#include <iostream>
#include "Geometric_Object.h"

using namespace std;

class Triangle : public Geometric_Object {
public:
    Triangle();
    Triangle(Vector a0, Vector b0, Vector c0, Colour col);

    Vector getA();
    Vector getB();
    Vector getC();
    virtual Colour getColour();
    Vector getNormal();
    double getDistance();

    virtual Vector getNormalAtPosition(Vector p);
    virtual double findIntersection(Ray ray);

private:
    Vector a, b, c;
    Vector normal;
    double distance;
    Colour colour;
};


#endif //C_RAYTRACER_TRIANGLE_H
