//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_VECTOR_H
#define C_RAYTRACER_VECTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Vector{

public:
    Vector();
    Vector(double x0, double y0, double z0);
    virtual ~Vector();

    double magnitude();
    Vector negative();
    Vector normalized();
    Vector scalar(double scalar);
    double dot(Vector v);
    Vector cross(Vector v);
    Vector add(Vector v);
    Vector subtract(Vector v);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

private:
    double x, y, z;
};

#endif //C_RAYTRACER_VECTOR_H
