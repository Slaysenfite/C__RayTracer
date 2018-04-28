//
// Created by wesse on 2018/04/04.
//

#include "Ray.h"

Ray::~Ray() {

}

Ray::Ray() {
    origin = Vector(0, 0, 0);
    direction = Vector(1, 0, 0);
}

Ray::Ray(Vector o, Vector d) {
    origin = o;
    direction = d;
}
Vector Ray::getDirection() {
    return direction;
}

Vector Ray::getOrigin() {
    return origin;
}

