//
// Created by wesse on 2018/04/05.
//

#include <cmath>
#include "Utilities.h"
#include "../Geometry_Utilities/Triangle.h"

void Utilities::saveBitmapImage(const char *filename, int w, int h, int dpi, RGBType *data) {
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int fileSize = 54 + s;

    double factor = 39.375;
    int m = static_cast<int>(factor);

    int ppm = dpi*m;

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    bmpfileheader[ 2] = (unsigned char)(fileSize);
    bmpfileheader[ 3] = (unsigned char)(fileSize>>8);
    bmpfileheader[ 4] = (unsigned char)(fileSize>>16);
    bmpfileheader[ 5] = (unsigned char)(fileSize>>24);

    bmpinfoheader[ 4] = (unsigned char)(w);
    bmpinfoheader[ 5] = (unsigned char)(w>>8);
    bmpinfoheader[ 6] = (unsigned char)(w>>16);
    bmpinfoheader[ 7] = (unsigned char)(w>>24);

    bmpinfoheader[ 8] = (unsigned char)(h);
    bmpinfoheader[ 9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    bmpinfoheader[21] = (unsigned char)(s);
    bmpinfoheader[22] = (unsigned char)(s>>8);
    bmpinfoheader[23] = (unsigned char)(s>>16);
    bmpinfoheader[24] = (unsigned char)(s>>24);

    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm>>8);
    bmpinfoheader[27] = (unsigned char)(ppm>>16);
    bmpinfoheader[28] = (unsigned char)(ppm>>24);

    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm>>8);
    bmpinfoheader[31] = (unsigned char)(ppm>>16);
    bmpinfoheader[32] = (unsigned char)(ppm>>24);

    f = fopen(filename,"wb");

    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    for (int i = 0; i < k; i++) {
        RGBType rgb = data[i];

        double red = (data[i].r)*255;
        double green = (data[i].g)*255;
        double blue = (data[i].b)*255;

        unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};

        fwrite(color,1,3,f);
    }

    fclose(f);
}

int Utilities::winningObjectIndex(vector<double> intersections) {
    int iMin; //index of winning object

    if(intersections.size() == 0) return -1; //if no intersections occur
    else if(intersections.size() == 1){
        if(intersections.at(0) > 0) return 0; //returns index 0
        else return -1;
    }
    else{ //for multiple intersections, the maximum values must first be found

        double max = intersections.at(0);
        for(int c = 1; c < intersections.size(); c++){
            if(max < intersections.at(c))
                max = intersections.at(c);
        }

        if(max > 0){
            for(int d = 0; d < intersections.size(); d++){
                if (intersections.at(d) > 0 && intersections.at(d) <= max) {
                    max = intersections.at(d);
                    iMin = d;
                }
            }
            return iMin;
        }
        else return -1;
    }
}

Colour Utilities::getColorAt(Vector intersection_position, Vector intersecting_ray_direction,
                             vector<Geometric_Object *> scene_objects, int index_of_winning_object,
                             vector<Light_Source *> light_sources, double accuracy, double ambientlight) {
    return Colour();
}

void Utilities::createPolygon(Vector c1, Vector c2, Colour colour, vector<Geometric_Object*> scene_objects) {
    Vector A = Vector(c2.getX(), c1.getY(), c1.getZ());
    Vector B = Vector(c2.getX(), c1.getY(), c2.getZ());
    Vector C = Vector(c1.getX(), c1.getY(), c2.getZ());

    Vector D = Vector(c2.getX(), c2.getY(), c1.getZ());
    Vector E = Vector(c1.getX(), c2.getY(), c1.getZ());
    Vector F = Vector(c1.getX(), c2.getY(), c2.getZ());

    //Left
    scene_objects.push_back(new Triangle (D, A, c1, colour));
    scene_objects.push_back(new Triangle (c1, E, D, colour));
    //Back
    scene_objects.push_back(new Triangle (c2, B, A, colour));
    scene_objects.push_back(new Triangle (A, D, c2, colour));
    //Right
    scene_objects.push_back(new Triangle (F, C, B, colour));
    scene_objects.push_back(new Triangle (B, c2, F, colour));
    //Front
    scene_objects.push_back(new Triangle (E, c1, C, colour));
    scene_objects.push_back(new Triangle (C, F, E, colour));
    //Top
    scene_objects.push_back(new Triangle (D, E, F, colour));
    scene_objects.push_back(new Triangle (F, c2, D, colour));
    //Bottom
    scene_objects.push_back(new Triangle (c1, A, B, colour));
    scene_objects.push_back(new Triangle (B, C, c1, colour));;

}
