//
// Created by wesse on 2018/04/04.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#include "Vector.h"
#include "Camera.h"
#include "Colour.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include "RGBType.h"
#include "Utilities.h"

using namespace std;

int main() {
    int var;
    Utilities util = Utilities();

    cout << "Rendering image...please wait indefinitely" << endl;

    int width = 640;
    int height = 480;
    double aspectRatio = (double)width/(double)height;
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
    Plane scene_object1 = Plane(Y, -1, light_black);
    Sphere scene_object2 = Sphere(O, 1, light_bloodred);

    vector<Geometric_Object*> scene_objects;
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object1));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object2));

    double xOffset, yOffset;

    const long double sysTimeStart = time(0);
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){

            var = x + y*width;

            //No anti aliasing
            if(width > height){
                xOffset = ((x + 0.5)/width)*aspectRatio - (((width - height)/(double)height)/2);
                yOffset = ((height - y) + 0.5)/height;
            }
            else if (height > width){
                xOffset = (x + 0.5)/ width;
                yOffset = (((height - y) + 0.5)/height)/aspectRatio - (((height - width)/(double)width)/2);
            }
			else if (width == height){
                xOffset = (x + 0.5)/width;
                yOffset = ((height - y) + 0.5)/height;
			}

            Vector rayOrigin = c.getCameraPosition(); //rays originate from camera position
            Vector rayDirection = cDir+(cRight*(xOffset - 0.5))+(cDown*(yOffset - 0.5)).normalized();

            Ray ray = Ray(rayOrigin, rayDirection);

            vector<double> intersections;

            for(int i = 0; i < scene_objects.size(); i++)
                intersections.push_back(scene_objects.at(i)->findIntersection(ray));

            int winningIndex = util.winningObjectIndex(intersections);;

            pixels[var].r = 134;
            pixels[var].g = 165;
            pixels[var].b = 98;
        }
    }

    util.saveBitmapImage("RayTracedImage.bmp", width, height, dpi, pixels);

    const long double sysTimeEnd = time(0);
    long double sysTimeTotal = sysTimeEnd - sysTimeStart;
    cout << "Rendering took " << sysTimeTotal << "s" << endl;
    return 0;
}