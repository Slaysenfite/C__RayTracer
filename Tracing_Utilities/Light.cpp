//
// Created by wesse on 2018/04/04.
//

#include "Light.h"

Light::Light() {
    position = Vector(0, 0, 0);
    colour = Colour(1, 1, 1, 0);
}

Light::Light(Vector pos, Colour col) {
    position = pos;
    colour = col;
}

Vector Light::getPosition() {
    return position;
}

Colour Light::getColour() {
    return colour;
}


