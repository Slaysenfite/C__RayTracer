//
// Created by wesse on 2018/04/04.
//

#include "Camera.h"

Vector Camera::getCameraPosition() {
    return cameraPosition;
}

Vector Camera::getCameraDirection() {
    return cameraDirection;
}

Vector Camera::getCameraRight() {
    return cameraRight;
}

Vector Camera::getCameraDown() {
    return cameraDown;
}

Camera::Camera() {
    cameraPosition = Vector (0, 0, 0);
    cameraDirection = Vector (0, 0, 1);
    cameraRight = Vector (0, 0, 0);
    cameraDown = Vector (0, 0, 0);
}

Camera::Camera(Vector cPos, Vector cDir, Vector cRight, Vector cDown) {
    cameraPosition = cPos;
    cameraDirection = cDir;
    cameraRight = cRight;
    cameraDown = cDown;
}
