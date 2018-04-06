//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_CAMERA_H

#include <iostream>
#include "Vector.h"

using namespace std;

class Camera{
public:
    Camera();
    Camera (Vector cPos, Vector cDir, Vector cRight, Vector cDown);

    Vector getCameraPosition();
    Vector getCameraDirection();
    Vector getCameraRight();
    Vector getCameraDown();

private:
    Vector cameraPosition, cameraDirection, cameraRight, cameraDown;
};

#endif //C_RAYTRACER_CAMERA_H
