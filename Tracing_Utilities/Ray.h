//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_RAY_H
#define C_RAYTRACER_RAY_H

#include <iostream>
#include "../Math_Utilities/Vector.h"

using namespace std;

class Ray{
public:
    Ray();
    Ray(Vector o, Vector d);
    ~Ray();

    Vector getOrigin();
    Vector getDirection();

private:
    Vector origin, direction;
};

#endif //C_RAYTRACER_RAY_H
