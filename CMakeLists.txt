cmake_minimum_required(VERSION 3.8)
project(C__RayTracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vector.h Vector.cpp Ray.cpp Ray.h Camera.cpp Camera.h Colour.cpp Colour.h Light.cpp Light.h Sphere.cpp Sphere.h Geometric_Object.cpp Geometric_Object.h Plane.cpp Plane.h Utilities.cpp Utilities.h RGBType.h)
add_executable(C__RayTracer ${SOURCE_FILES})