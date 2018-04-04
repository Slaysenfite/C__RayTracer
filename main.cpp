//
// Created by wesse on 2018/04/04.
//

#include <iostream>
#include <cmath>
#include <ctime>

#include "Vector.h"
#include "Camera.h"
#include "Colour.h"
#include "Light.h"
#include "Sphere.h"

using namespace std;

struct RGBType{
    double r, g, b;
};

void saveBitmapImage(const char *filename, int w, int h, int dpi, RGBType *data){
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;

    double factor = 39.375;
    int m = static_cast<int>(factor);

    int ppm = dpi*m;

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    bmpfileheader[ 2] = (unsigned char)(filesize);
    bmpfileheader[ 3] = (unsigned char)(filesize>>8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

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

int main() {
    int var;

    cout << "Rendering image...please wait indefinitely" << endl;

    int width = 640;
    int height = 480;
    int pixelNum = width*height;

    int dpi = 72;

    RGBType *pixels = new RGBType[pixelNum];

    Vector cPos = Vector(3, 1.5, -4);

    Vector O = Vector();
    Vector X = Vector(1, 0, 0);
    Vector Y = Vector(0, 1, 0);
    Vector Z = Vector(0, 0, 1);

    Vector lookAt = Vector();
    Vector difference = Vector(cPos.getX() - lookAt.getX(),
                               cPos.getY() - lookAt.getY(),
                               cPos.getZ() - lookAt.getZ());
    Vector cDir = difference.negative().normalized();
    Vector cRight = (Y^cDir).normalized();
    Vector cDown = (cRight^cDir);

    Camera c = Camera(cPos, cDir, cRight, cDown);

    Colour light_white = Colour(1, 1, 1, 0);
    Colour light_greenish = Colour(100/255, 155/255, 80/255, 0.3);
    Colour light_bloodred = Colour(155/255, 8/255, 8/255, 0);
    Colour light_black = Colour(0, 0, 0, 0);

    Vector lightPos = Vector(-7, 10, -10);
    Light lighting = Light(lightPos, light_greenish);

    //Objects
    Sphere scene_object1 = Sphere(O, 1, light_bloodred);

    const long double sysTimeStart = time(0);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            var = x + y*width;
            pixels[var].r = 34;
            pixels[var].g = 165;
            pixels[var].b = 234;
        }
    }

    saveBitmapImage("RayTracedImage.bmp", width, height, dpi, pixels);

    const long double sysTimeEnd = time(0);
    long double sysTimeTotal = sysTimeEnd - sysTimeStart;
    cout << "Rendering took " << sysTimeTotal << "s" << endl;
    return 0;
}