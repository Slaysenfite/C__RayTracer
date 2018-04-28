cmake_minimum_required(VERSION 3.8)
project(C__RayTracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Math_Utilities/Vector.h Math_Utilities/Vector.cpp Tracing_Utilities/Ray.cpp
        Tracing_Utilities/Ray.h Tracing_Utilities/Camera.cpp Tracing_Utilities/Camera.h Tracing_Utilities/Colour.cpp
        Tracing_Utilities/Colour.h Tracing_Utilities/Light.cpp Tracing_Utilities/Light.h Geometry_Utilities/Sphere.cpp
        Geometry_Utilities/Sphere.h Geometry_Utilities/Geometric_Object.cpp Geometry_Utilities/Geometric_Object.h
        Geometry_Utilities/Plane.cpp Geometry_Utilities/Plane.h General_Utilities/Utilities.cpp
        General_Utilities/Utilities.h Tracing_Utilities/RGBType.h Tracing_Utilities/Light_Source.cpp
        Tracing_Utilities/Light_Source.h Geometry_Utilities/Triangle.cpp Geometry_Utilities/Triangle.h)
add_executable(C__RayTracer ${SOURCE_FILES})