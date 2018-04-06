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
#include "Triangle.h"

using namespace std;

int var;
vector<Geometric_Object*> scene_objects;

void createPolygon(Vector c1, Vector c2, Colour colour) {
    Vector A = Vector(c2.getX(), c1.getY(), c1.getZ());
    Vector B = Vector(c2.getX(), c1.getY(), c2.getZ());
    Vector C = Vector(c1.getX(), c1.getY(), c2.getZ());

    Vector D = Vector(c2.getX(), c2.getY(), c1.getZ());
    Vector E = Vector(c1.getX(), c2.getY(), c1.getZ());
    Vector F = Vector(c1.getX(), c2.getY(), c2.getZ());;

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
    scene_objects.push_back(new Triangle (B, C, c1, colour));
}

int main() {
    const long double sysTimeStart = time(0);

    Utilities util = Utilities();

    cout << "Rendering image...please wait indefinitely" << endl;

    int width = 640;
    int height = 480;
    double aspectRatio = (double)width/(double)height;
    int pixelNum = width*height;

    int dpi = 72;

    RGBType *pixels = new RGBType[pixelNum];

    Vector cPos = Vector(3, 1.5, -4);

    Vector O = Vector(0, 0, 0);
    Vector X = Vector(1, 0, 0);
    Vector Y = Vector(0, 1, 0);
    Vector Z = Vector(0, 0, 1);

    Vector lookAt = Vector(0, 0, 0);
    Vector difference = Vector(cPos.getX() - lookAt.getX(),
                               cPos.getY() - lookAt.getY(),
                               cPos.getZ() - lookAt.getZ());
    Vector cDir = difference.negative().normalized();
    Vector cRight = Y.cross(cDir).normalized();
    Vector cDown = cRight.cross(cDir);

    Camera c = Camera(cPos, cDir, cRight, cDown);

    Colour light_white = Colour(1, 1, 1, 0);
    Colour pretty_green = Colour(0.5, 1.0, 0.5, 0.3);
    Colour brown = Colour(0.7, 0.5, 0.25, 0.2);
    Colour reddish = Colour(0.9, 0.4, 0.1, 0);
    Colour grey = Colour(0.5, 0.5, 0.5, 0);
    Colour bluish = Colour(0.15, 0.2, 1, 0);
    Colour light_black = Colour(0, 0, 0, 0);

    Vector lightPos = Vector(-7, 10, -10);
    Light lighting = Light(lightPos, light_white);

    ///Objects
    Plane scene_object1 = Plane(Y, -1, pretty_green);
    Sphere scene_object2 = Sphere(O, 1, grey);
    Sphere scene_object3 = Sphere(Vector(-10, 3, 5), 4, bluish);
    Sphere scene_object4 = Sphere(Vector(2.2, 0.8, -1), 0.25, light_white);
    Triangle scene_object5 = Triangle(Vector(-0.5, 0, 5), Vector(4, 0, 2), Vector(2.5, 3, 2), brown);

    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object1));
    //scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object2));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object3));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object4));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object5));
    createPolygon(Vector(1, 1, 1), Vector(-1, -1, -1), grey);



    double xOffset, yOffset;

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
            Vector rayDirection = cDir.add(cRight.scalar(xOffset - 0.5)).add(cDown.scalar(yOffset - 0.5)).normalized();

            Ray ray = Ray(rayOrigin, rayDirection);

            vector<double> intersections;

            for(int i = 0; i < scene_objects.size(); i++){
                intersections.push_back(scene_objects.at(i)->findIntersection(ray));
            }

            int winningIndex = util.winningObjectIndex(intersections);

            if(winningIndex == util.NO_INTERSECTION){
                pixels[var].r = 0;
                pixels[var].g = 0;
                pixels[var].b = 0;
            }
            else{
                Colour varColour = scene_objects.at(winningIndex)->getColour();

                pixels[var].r = varColour.getRed();
                pixels[var].g = varColour.getGreen();
                pixels[var].b = varColour.getBlue();
            }

        }
    }

    util.saveBitmapImage("RayTracedImage.bmp", width, height, dpi, pixels);

    const long double sysTimeEnd = time(0);
    long double sysTimeTotal = sysTimeEnd - sysTimeStart;
    cout << "Rendering took " << sysTimeTotal << "s" << endl;
    return 0;
}