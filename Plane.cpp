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

Vector Plane::getNormal() {
    return normal;
}

double Plane::getDistanceFromOrigin() {
    return distanceFromOrigin;
}

Colour Plane::getColour() {
    return colour;
}

Vector Plane::getNormalVectorAt(Vector point) {
    return normal;
}

double Plane::findIntersection(Ray ray) {
    Vector rayDirection = ray.getDirection();
    double a = rayDirection.dot(normal);
    if(a == 0){
        //parallel ray
        return -1;
    }
    else{
        double b = normal.dot(ray.getOrigin().add(normal.scalar(distanceFromOrigin).negative()));
        return -1*b/a;
    }
}

