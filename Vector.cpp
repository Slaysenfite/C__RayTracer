//
// Created by wesse on 2018/04/04.
//

#include "Vector.h"
#include <math.h>

Vector::~Vector() {

}

Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(double x0, double y0, double z0) {
    x = x0;
    y = y0;
    z = z0;
}

double Vector::magnitude() {
    return sqrt((x*x) + (y*y) + (z*z));
}

Vector Vector::normalized() {
    double m = this->magnitude();
    return Vector(x/m, y/m, z/m);
}

double Vector::dot(Vector v) {
    return x*v.x + y*v.y + z*v.z;
}

Vector Vector::cross(Vector v) {
    return Vector(y*v.getZ() - z*v.getY(), z*v.getX() - x*v.getZ(), x*v.getY() - y*v.getX());
}

Vector Vector::scalar(double scalar) {
    return Vector(x*scalar, y*scalar, z*scalar);
}

Vector Vector::operator+ (const Vector& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z;
    return (*this);
}

Vector Vector::operator- (const Vector& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z;
    return (*this);
}

Vector Vector::operator*(const double scalar) {
    return Vector(x*scalar, y*scalar, z*scalar);
}

double Vector::operator*(const Vector &v) {
    return x*v.getX() + y*v.getY() + z*v.getZ();
}

Vector Vector::operator^(const Vector &v) {
    return Vector(y*v.getZ() - z*v.getY(), z*v.getX() - x*v.getZ(), x*v.getY() - y*v.getX());
}

double Vector::getX() const {
    return x;
}

void Vector::setX(double x) {
    Vector::x = x;
}

double Vector::getY() const {
    return y;
}

void Vector::setY(double y) {
    Vector::y = y;
}

double Vector::getZ() const {
    return z;
}

void Vector::setZ(double z) {
    Vector::z = z;
}

Vector Vector::negative() {
    return Vector(-x, -y, -z);
}

Vector Vector::multiply(Vector v) {
    return Vector(x*v.getX(), y*v.getY(), z*v.getZ());
}
