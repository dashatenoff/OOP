#include <iostream>
#include <cmath>

#ifndef UNTITLED2_VECTOR_H
#define UNTITLED2_VECTOR_H

class Vector{
public:
    Vector(){
        x = 0.0;
        y = 0.0;
        id = (ID++);
    }

    Vector(double x, double y){
        setX(x);
        setY(y);
        id = (ID++);
    }

    int getID() const {
        return id;
    }

    void setX (double valX){
        this -> x = valX;
    }
    void setY (double valY){
        this -> y = valY;
    }

    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }

    double dist() const {
        return std::sqrt(x*x+y*y);
    }

    Vector operator+(const Vector& other) const{
        return Vector(this->x + other.x, this->y + other.y);
    }

    double operator*(const Vector& other) const{
        return (this->x * other.x + this->y * other.y);
    }

    double distTo(const Vector& other) const {
        double dx = this->x - other.x;
        double dy = this->y - other.y;
        return std::sqrt(dx*dx + dy*dy);
    }

private:
    inline static int ID = 0;
    double x;
    double y;
    int id;
};

#endif //UNTITLED2_VECTOR_H
