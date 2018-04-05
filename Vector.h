//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_VECTOR_H
#define C_RAYTRACER_VECTOR_H

#include <iostream>

using namespace std;

class Vector{

public:
    Vector();
    Vector(double x0, double y0, double z0);
    virtual ~Vector();

    double magnitude();
    Vector negative();
    Vector normalized();
    Vector multiply(Vector v);
    Vector scalar(double scalar);

    double dot(Vector v);
    Vector cross(Vector v);

    Vector operator+ (const Vector& rhs);
    Vector operator- (const Vector& rhs);
    Vector operator*(const double scalar); //scalar multiplication
    double operator* (const Vector& rhs); //dot product
    Vector operator^ (const Vector& rhs); //cross product

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
