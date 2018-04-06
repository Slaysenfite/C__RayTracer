//
// Created by wesse on 2018/04/05.
//

#include "Triangle.h"

Triangle::Triangle() {
    a = Vector(1, 0, 0);
    b = Vector(0, 1, 0);
    c = Vector(0, 0, 1);
    colour = Colour(0.5, 0.5, 0.5, 0);
}

Triangle::Triangle(Vector a0, Vector b0, Vector c0, Colour col) {
    a = a0;
    b = b0;
    c = c0;
    colour = col;
}

Vector Triangle::getA() {
    return a;
}

Vector Triangle::getB()  {
    return b;
}

Vector Triangle::getC() {
    return c;
}

Colour Triangle::getColour() {
    return colour;
}

Vector Triangle::getNormal() {
    Vector CA = Vector(c.getX() - a.getX(), c.getY() - a.getY(), c.getZ() - a.getZ());
    Vector BA = Vector(b.getX() - a.getX(), b.getY() - a.getY(), b.getZ() - a.getZ());
    normal = (CA.cross(BA)).normalized();
    return normal;
}

double Triangle::getDistance() {
    normal = getNormal();
    return normal.dot(a);
}

double Triangle::findIntersection(Ray ray) {
    Vector rayDirection = ray.getDirection();
    Vector rayOrigin = ray.getOrigin();

    double distance = getDistance();
    normal = getNormal();

    double u = rayDirection.dot(normal);
    if(u == 0){
        //parallel ray
        return -1;
    }
    else{
        double w = normal.dot(ray.getOrigin().add(normal.scalar(distance).negative()));
        double distanceToPlane = -1*w/u;

        double xQ = (rayDirection.scalar(distanceToPlane)).getX() + rayOrigin.getX();
        double yQ = (rayDirection.scalar(distanceToPlane)).getY() + rayOrigin.getY();
        double zQ = (rayDirection.scalar(distanceToPlane)).getZ() + rayOrigin.getZ();


        Vector q = Vector(xQ, yQ, zQ);

        Vector CA = Vector(c.getX() - a.getX(), c.getY() - a.getY(), c.getZ() - a.getZ());
        Vector BC = Vector(b.getX() - c.getX(), b.getY() - c.getY(), b.getZ() - c.getZ());
        Vector AB = Vector(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());

        Vector QA = Vector(q.getX() - a.getX(), q.getY() - a.getY(), q.getZ() - a.getZ());
        Vector QB = Vector(q.getX() - b.getX(), q.getY() - b.getY(), q.getZ() - b.getZ());
        Vector QC = Vector(q.getX() - c.getX(), q.getY() - c.getY(), q.getZ() - c.getZ());

        if( (CA.cross(QA)).dot(normal) >= 0 &&  (BC.cross(QC)).dot(normal)  >= 0 && (AB.cross(QB)).dot(normal) >= 0 ){ //inside triangle
            return distanceToPlane;
        }
        else return -1;
    }
}

Vector Triangle::getNormalAtPosition(Vector p) {
    normal = getNormal();
    return normal;
}







