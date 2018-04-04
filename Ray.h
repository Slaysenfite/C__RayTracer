//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_RAY_H
#define C_RAYTRACER_RAY_H

#include <iostream>
#include "Vector.h"

using namespace std;

class Ray{
public:
    Ray();
    Ray(Vector o, Vector d);
    ~Ray();

    const Vector &getOrigin() const;
    void setOrigin(const Vector &origin);
    const Vector &getDirection() const;
    void setDirection(const Vector &direction);

private:
    Vector origin, direction;
};

#endif //C_RAYTRACER_RAY_H
