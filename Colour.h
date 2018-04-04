//
// Created by wesse on 2018/04/04.
//

#ifndef C_RAYTRACER_COLOUR_H
#define C_RAYTRACER_COLOUR_H

#include <iostream>

using namespace std;

class Colour {
public:
    Colour();
    Colour(double r, double g, double b, double s);

    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    double getSpecial() const;

    void setRed(double red);
    void setGreen(double green);
    void setBlue(double blue);
    void setSpecial(double special);

    Colour& operator+ (const Colour& rhs);
    Colour& operator- (const Colour& rhs);
    Colour operator*(const double scalar); //scalar multiplication
    Colour operator*(const Colour& rhs); //colour multiplication

    Colour average(Colour c);
    double brightness();
    Colour clip();

private:
    double red, green, blue, special;
};


#endif //C_RAYTRACER_COLOUR_H
