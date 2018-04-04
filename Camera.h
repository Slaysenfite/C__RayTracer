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

    const Vector &getCameraPosition() const;
    const Vector &getCameraDirection() const;
    const Vector &getCameraRight() const;
    const Vector &getCameraDown() const;

private:
    Vector cameraPosition, cameraDirection, cameraRight, cameraDown;
};

#endif //C_RAYTRACER_CAMERA_H
