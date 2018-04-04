//
// Created by wesse on 2018/04/04.
//

#include "Geometric_Object.h"
Geometric_Object::Geometric_Object() {}

virtual Colour Geometric_Object::getColor () {
    return Colour(0, 0, 0, 0);
}

virtual Vector Geometric_Object::getNormalAt(Vector intersection_position) {
    return Vector();
}

virtual double Geometric_Object::findIntersection(Ray ray) {
    return 0;
}