cmake_minimum_required(VERSION 3.28)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2 main.cpp
        Vector.h
        Point3D.h
        Point2D.h
        VectorCollection.h
        matrix/main.c
        matrix/matrix.h
        matrix/field_info.h
        matrix/field_info.c
        matrix/matrix.c
        matrix/tests.h
        matrix/tests.c
)
