//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_PLANE_H
#define C_RAYTRACER_PLANE_H

#include <iostream>
#include "Vector.h"
#include "Colour.h"
#include "Ray.h"
#include "Geometric_Object.h"

using namespace std;

class Plane : public Geometric_Object{
public:
    Plane();
    Plane(Vector n, double dfo, Colour c);

    const Vector &getNormal() const;
    double getDistanceFromOrigin() const;
    const Colour &getColour() const;

    Vector getNormalVectorAt(Vector point);
    double findIntersection(Ray ray);

private:
    Vector normal;
    double distanceFromOrigin;
    Colour colour;

};


#endif //C_RAYTRACER_PLANE_H
