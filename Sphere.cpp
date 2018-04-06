//
// Created by wesse on 2018/04/04.
//

#include <cmath>
#include "Sphere.h"

Sphere::Sphere() {
    center = Vector(0, 0, 0);
    radius = 1.0;
    colour = Colour(0.5, 0.5, 0.5, 0);
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

double Sphere::findIntersection(Ray ray) {
    Vector rayOrigin = ray.getOrigin();

    double xROrigin = rayOrigin.getX();
    double yROrigin = rayOrigin.getY();
    double zROrigin = rayOrigin.getZ();

    Vector rayDirection = ray.getDirection();

    double xRDirection = rayDirection.getX();
    double yRDirection = rayDirection.getY();
    double zRDirection = rayDirection.getZ();

    Vector sphereCenter = center;

    double xSCenter = sphereCenter.getX();
    double ySCenter = sphereCenter.getY();
    double zSCenter = sphereCenter.getZ();

    double a = 1;
    double b = (2*(xROrigin - xSCenter)*xRDirection)
            + (2*(yROrigin - ySCenter)*yRDirection)
            + (2*(zROrigin - zSCenter)*zRDirection);
    double c = pow(xROrigin - xSCenter, 2)
            + pow(yROrigin - ySCenter, 2)
            + pow(zROrigin - zSCenter, 2)
            - (radius*radius);

    double discriminant = b*b - 4*c;

    if(discriminant > 0){ //ray intersects
        double firstRoot = ((-1*b - sqrt(discriminant))/2) - 0.000001;
        //find smallest positive root
        if(firstRoot > 0) return firstRoot;
        else return ((sqrt(discriminant) - b)/2) - 0.000001;
    }
    else return -1; //ray misses
}

Vector Sphere::getNormalAt(Vector position) {
    Vector normalToPosition = position.add(center.negative()).normalized();
    return normalToPosition;
}

