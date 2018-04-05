//
// Created by wesse on 2018/04/04.
//

#include "Geometric_Object.h"
Geometric_Object::Geometric_Object() {}

Vector Geometric_Object::getNormalAt(Vector intersection_position) {
    return Vector();
}

double Geometric_Object::findIntersection(Ray ray) {
    return 0;
}

Colour Geometric_Object::getColour() {
    return Colour(0, 0, 0, 0);
}



