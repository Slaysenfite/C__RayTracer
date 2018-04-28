//
// Created by wesse on 2018/04/04.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#include "Math_Utilities/Vector.h"
#include "Tracing_Utilities/Camera.h"
#include "Tracing_Utilities/Colour.h"
#include "Tracing_Utilities/Light.h"
#include "Geometry_Utilities/Sphere.h"
#include "Geometry_Utilities/Plane.h"
#include "Tracing_Utilities/RGBType.h"
#include "General_Utilities/Utilities.h"
#include "Geometry_Utilities/Triangle.h"

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

Colour getColourAt(Vector intersection_position, Vector intersecting_ray_direction,
             vector<Geometric_Object *> scene_objects, int index_of_winning_object,
             vector<Light_Source *> light_sources, double accuracy, double ambientlight){

    Utilities util = Utilities();

    Colour winning_object_Colour = scene_objects.at(index_of_winning_object)->getColour();
    Vector winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);

    if (winning_object_Colour.getSpecial() == 2) {
        // checkered/tile floor pattern

        int square = (int)floor(intersection_position.getX()) + (int)floor(intersection_position.getZ());

        if ((square % 2) == 0) {
            // black tile
            winning_object_Colour.setRed(0);
            winning_object_Colour.setGreen(0);
            winning_object_Colour.setBlue(0);
        }
        else {
            // white tile
            winning_object_Colour.setRed(1);
            winning_object_Colour.setGreen(1);
            winning_object_Colour.setRed(1);
        }
    }

    Colour final_Colour = winning_object_Colour.scalar(ambientlight);

    if (winning_object_Colour.getSpecial() > 0 && winning_object_Colour.getSpecial() <= 1) {
        // reflection from objects with specular intensity
        double dot1 = winning_object_normal.dot(intersecting_ray_direction.negative());
        Vector scalar1 = winning_object_normal.scalar(dot1);
        Vector add1 = scalar1.add(intersecting_ray_direction);
        Vector scalar2 = add1.scalar(2);
        Vector add2 = intersecting_ray_direction.negative().add(scalar2);
        Vector reflection_direction = add2.normalized();

        Ray reflection_ray (intersection_position, reflection_direction);

        // determine what the ray intersects with first
        vector<double> reflection_intersections;

        for (int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index++) {
            reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
        }

        int index_of_winning_object_with_reflection = util.winningObjectIndex(reflection_intersections);

        if (index_of_winning_object_with_reflection != -1) {
            // reflection ray missed everthing else
            if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
                // determine the position and direction at the point of intersection with the reflection ray
                // the ray only affects the Colour if it reflected off something

                Vector reflection_intersection_position = intersection_position.add(reflection_direction.scalar(reflection_intersections.at(index_of_winning_object_with_reflection)));
                Vector reflection_intersection_ray_direction = reflection_direction;

                Colour reflection_intersection_Colour = getColourAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientlight);

                final_Colour = final_Colour.add(reflection_intersection_Colour.scalar(winning_object_Colour.getSpecial()));
            }
        }
    }

    for (int light_index = 0; light_index < light_sources.size(); light_index++) {
        Vector light_direction = light_sources.at(light_index)->getLightPosition().add(intersection_position.negative()).normalized();

        float cosine_angle = winning_object_normal.dot(light_direction);

        if (cosine_angle > 0) {
            // test for shadows
            bool shadowed = false;

            Vector distance_to_light = light_sources.at(light_index)->getLightPosition().add(intersection_position.negative()).normalized();
            float distance_to_light_magnitude = distance_to_light.magnitude();

            Ray shadow_ray (intersection_position, light_sources.at(light_index)->getLightPosition().add(intersection_position.negative()).normalized());

            vector<double> secondary_intersections;

            for (int object_index = 0; object_index < scene_objects.size() && shadowed == false; object_index++) {
                secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));
            }

            for (int c = 0; c < secondary_intersections.size(); c++) {
                if (secondary_intersections.at(c) > accuracy) {
                    if (secondary_intersections.at(c) <= distance_to_light_magnitude) {
                        shadowed = true;
                    }
                    break;
                }
            }

            if (shadowed == false) {
                final_Colour = final_Colour.add(winning_object_Colour.multiply(light_sources.at(light_index)->getLightColour()).scalar(cosine_angle));

                if (winning_object_Colour.getSpecial() > 0 && winning_object_Colour.getSpecial() <= 1) {
                    // special [0-1]
                    double dot1 = winning_object_normal.dot(intersecting_ray_direction.negative());
                    Vector scalar1 = winning_object_normal.scalar(dot1);
                    Vector add1 = scalar1.add(intersecting_ray_direction);
                    Vector scalar2 = add1.scalar(2);
                    Vector add2 = intersecting_ray_direction.negative().add(scalar2);
                    Vector reflection_direction = add2.normalized();

                    double specular = reflection_direction.dot(light_direction);
                    if (specular > 0) {
                        specular = pow(specular, 10);
                        final_Colour = final_Colour.add(light_sources.at(light_index)->getLightColour().scalar(specular*winning_object_Colour.getSpecial()));
                    }
                }

            }

        }
    }

    return final_Colour.clip();
}

int main() {
    const long double sysTimeStart = time(0);

    Utilities util = Utilities();
    //Scene scene = Scene();
    cout << "Rendering image...please wait indefinitely" << endl;

    int width = 1200;
    int height = 800;

    /*int width = 1900;
    int height = 1280;*/

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

    //colours
    Colour light_white = Colour(1, 1, 1, 0);
    Colour light_red = Colour(1, 0, 0, 0);
    Colour greenish = Colour(0.5, 1.0, 0.5, 0.3);
    Colour brown = Colour(0.7, 0.5, 0.25, 0.2);
    Colour reddish = Colour(0.9, 0.2, 0.2, 0);
    Colour grey = Colour(0.5, 0.5, 0.5, 0);
    Colour navy = Colour(0.25, 0.33, 0.67, 0);
    Colour bluish = Colour(0.15, 0.2, 1, 0);
    Colour light_black = Colour(0, 0, 0, 0);

    Colour white_light (1.0, 1.0, 1.0, 0);
    Colour red (1, 0, 0, 0);
    Colour green (0, 1, 0, 0);
    Colour blue (0, 0, 1, 0);
    Colour pretty_green (0.5, 1.0, 0.5, 0.3);
    Colour maroon (0.7, 0.5, 0.25, 0.2);
    Colour tile_floor (1, 1, 1, 2);
    Colour gray (0.5, 0.5, 0.5, 0);
    Colour black (0.0, 0.0, 0.0, 0);
    Colour light_greenish = Colour(100/255, 155/255, 80/255, 0.3);
    Colour light_bloodred = Colour(155/255, 8/255, 8/255, 0);

    Vector light_position (4, 2, -1);
    Light scene_light (light_position, white_light);
    vector<Light_Source*> light_sources;
    light_sources.push_back(dynamic_cast<Light_Source*>(&scene_light));

    // scene objects
    Sphere scene_object2 = Sphere(Vector(-2, 0.5, 0), 1, maroon);
    Sphere scene_object3 = Sphere(O, 1, pretty_green);
    Sphere scene_object4 = Sphere(Vector(+2, 2, -1), 0.25, white_light);
    Triangle scene_object5 = Triangle(Vector(-0.5, 0, 5), Vector(4, 0, 2), Vector(2.5, 3, 2), brown);

    Plane scene_plane (Y, -1, tile_floor);
    vector<Geometric_Object*> scene_objects;

    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_plane));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object2));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object3));
    //scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object4));
    scene_objects.push_back(dynamic_cast<Geometric_Object*>(&scene_object5));




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
                if(intersections.at(winningIndex) > util.ACCURACY_CHECK){
                    Vector intersectionPosition = rayOrigin.add(rayDirection.scalar(intersections.at(winningIndex)));
                    Vector intersectionRayDirection = rayDirection;

                    Colour intersectionColour = getColourAt(intersectionPosition, intersectionRayDirection, scene_objects,
                                                           winningIndex, light_sources, util.ACCURACY_CHECK, util.AMBIENT_LIGHT);

                    pixels[var].r = intersectionColour.getRed();
                    pixels[var].g = intersectionColour.getGreen();
                    pixels[var].b = intersectionColour.getBlue();
                }
            }
        }
    }

    util.saveBitmapImage("RayTracedImage.bmp", width, height, dpi, pixels);

    const long double sysTimeEnd = time(0);
    long double sysTimeTotal = sysTimeEnd - sysTimeStart;
    cout << "Rendering took " << sysTimeTotal << "s" << endl;
    return 0;
}