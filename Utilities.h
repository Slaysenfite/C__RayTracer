//
// Created by wesse on 2018/04/05.
//

#ifndef C_RAYTRACER_UTILITES_H
#define C_RAYTRACER_UTILITES_H

#include <iostream>
#include <vector>
#include "RGBType.h"
#include "Light_Source.h"
#include "Geometric_Object.h"

using namespace std;

class Utilities {
public:
    const int NO_INTERSECTION = -1;

    static void saveBitmapImage(const char *filename, int w, int h, int dpi, RGBType *data);
    static int winningObjectIndex(vector<double> intersections);
    static Colour getColorAt(Vector intersection_position, Vector intersecting_ray_direction, vector<Geometric_Object*> scene_objects, int index_of_winning_object, vector<Light_Source*> light_sources, double accuracy, double ambientlight);
    static void createPolygon(Vector corner1, Vector corner2, Colour colour, vector<Geometric_Object*> scene_objects);
};


#endif //C_RAYTRACER_UTILITES_H
