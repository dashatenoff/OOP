#include <iostream>
#include <cmath>

#ifndef UNTITLED2_POINT3D_H
#define UNTITLED2_POINT3D_H

class Point3D {
public:
    Point3D() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Point3D(double x, double y, double z) {
        setX(x);
        setY(y);
        setZ(z);
    }

    void setX(double valX) {
        this->x = valX;
    }

    void setY(double valY) {
        this->y = valY;
    }

    void setZ(double valZ) {
        this->z = valZ;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }

    double dist() const {
        return std::sqrt(x * x + y * y + z * z);
    }

protected:
    double x;
    double y;
    double z;
};



#endif // UNTITLED2_POINT3D_H
