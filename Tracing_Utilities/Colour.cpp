//
// Created by wesse on 2018/04/04.
//

#include "Colour.h"

Colour::Colour() {
    red = 0.5;
    green = 0.5;
    blue = 0.5;
}

Colour::Colour(double r, double g, double b, double s) {
    red = r;
    green = g;
    blue = b;
    special = s;
}

double Colour::getRed() {
    return red;
}

double Colour::getGreen() {
    return green;
}

double Colour::getBlue() {
    return blue;
}

double Colour::getSpecial() {
    return special;
}

void Colour::setRed(double red) {
    Colour::red = red;
}

void Colour::setGreen(double green) {
    Colour::green = green;
}

void Colour::setBlue(double blue) {
    Colour::blue = blue;
}

void Colour::setSpecial(double special) {
    Colour::special = special;
}

Colour Colour::average(Colour c) {
    return Colour((red + c.getRed())/2,
            (green + c.getGreen())/2,
            (blue + c.getBlue())/2,
                  special);

}

double Colour::brightness() {
    return (red + green + blue)/3;
}

Colour Colour::clip() {
    double totalLight = red + green + blue;
    double excessLight = totalLight - 3;
    if(excessLight > 0){
        red = red + excessLight * (red/totalLight);
        green = green + excessLight * (green/totalLight);
        blue = blue + excessLight * (blue/totalLight);
    }
    if(red > 1) red = 1;
    if(green > 1) green = 1;
    if(blue > 1) blue = 1;
    if(red < 0) red = 0;
    if(green < 0) green = 0;
    if(blue < 0) blue = 0;

    return Colour(red, green, blue, special);
}

Colour Colour::scalar(double scalar) {
    return Colour(red*scalar, green*scalar, blue*scalar, special);
}

Colour Colour::add(Colour c) {
    return Colour(red + c.getRed(), green + c.getGreen(), blue + c.getBlue(), special);
}

Colour Colour::subtract(Colour c) {
    return Colour(red - c.getRed(), green - c.getGreen(), blue - c.getBlue(), special);
}

Colour Colour::multiply(Colour c) {
    return Colour(red*c.getRed(), green*c.getGreen(), blue*c.getBlue(), special);
}
