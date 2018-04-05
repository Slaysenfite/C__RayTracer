//
// Created by wesse on 2018/04/04.
//

#include "Plane.h"

Plane::Plane() {
    normal = Vector(1, 0, 0);
    distanceFromOrigin = 0;
    colour = Colour(0.5, 0.5, 0.5, 0);
}

Plane::Plane(Vector n, double dfo, Colour c) {
    normal = n;
    distanceFromOrigin = dfo;
    colour = c;
}

const Vector &Plane::getNormal() const {
    return normal;
}

double Plane::getDistanceFromOrigin() const {
    return distanceFromOrigin;
}

const Colour &Plane::getColour() const {
    return colour;
}

Vector Plane::getNormalVectorAt(Vector point) {
    return normal;
}

double Plane::findIntersection(Ray ray) {
    Vector rayDirection = ray.getDirection();
    double a = rayDirection*normal;
    if(a == 0){
        //parallel ray
        return -1;
    }
    else{
        Vector v1 = (normal*distanceFromOrigin).negative();
        Vector v2 = v1+ray.getOrigin();
        double b = normal*v2;
        return -1*b/a;
    }
}
