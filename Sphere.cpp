//
// Created by wesse on 2018/04/04.
//

#include "Sphere.h"

Sphere::Sphere() {
    center = Vector();
    radius = 1;
    colour = Colour(0.5, 0.5, 1, 0);
}

Sphere::Sphere(Vector v, double r, Colour c) {
    center = v;
    radius = r;
    colour = c;
}

Vector  Sphere::getCenter(){
    return center;
}

double Sphere::getRadius(){
    return radius;
}

Colour Sphere::getColour(){
    return colour;
}

