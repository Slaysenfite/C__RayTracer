//
// Created by wesse on 2018/04/05.
//

#ifndef C_RAYTRACER_UTILITES_H
#define C_RAYTRACER_UTILITES_H

#include <iostream>
#include <vector>
#include "RGBType.h"

using namespace std;

class Utilities {
public:
    static void saveBitmapImage(const char *filename, int w, int h, int dpi, RGBType *data);
    static int winningObjectIndex(vector<double> intersections);
};


#endif //C_RAYTRACER_UTILITES_H
