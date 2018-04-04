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
const Vector &Ray::getDirection() const {
    return direction;
}

void Ray::setDirection(const Vector &direction) {
    Ray::direction = direction;
}

const Vector &Ray::getOrigin() const {
    return origin;
}

void Ray::setOrigin(const Vector &origin) {
    Ray::origin = origin;
}

