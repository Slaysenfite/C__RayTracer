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

double Colour::getRed() const {
    return red;
}

double Colour::getGreen() const {
    return green;
}

double Colour::getBlue() const {
    return blue;
}

double Colour::getSpecial() const {
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

Colour &Colour::operator+(const Colour &rhs) {
    red += rhs.getRed();
    green += rhs.getGreen();
    blue += rhs.getBlue();
    return (*this);
}

Colour &Colour::operator-(const Colour &rhs) {
    red -= rhs.getRed();
    green -= rhs.getGreen();
    blue -= rhs.getBlue();
    return (*this);
}

Colour Colour::operator*(const double scalar) {
    return Colour(red*scalar, green*scalar,blue*scalar, special);
}

Colour Colour::operator*(const Colour &rhs) {
    return Colour(red*rhs.getRed(), green*rhs.getGreen(), blue*rhs.getBlue(), special);
}

Colour Colour::average(Colour c) {
    return Colour((red + c.getRed())/2,
            (green + c.getGreen())/2,
            (blue + c.getBlue())/2,
                  special);

}

double Colour::brightness() {
    return 0;
}

Colour Colour::clip() {
    return Colour();
}
