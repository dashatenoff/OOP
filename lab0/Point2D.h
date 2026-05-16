#include <iostream>
#include <cmath>
#include "Point3D.h"

#ifndef UNTITLED2_POINT2D_H
#define UNTITLED2_POINT2D_H

class Point2D : public Point3D {
public:
    Point2D() : Point3D(0.0, 0.0, 0.0) {}

    Point2D(double x, double y) : Point3D(x, y, 0.0) {}

private:
    using Point3D::z;
    using Point3D::getZ;
    using Point3D::setZ;
};

#endif // UNTITLED2_POINT2D_H
