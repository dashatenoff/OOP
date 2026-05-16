//#include <iostream>
//#include "Vector.h"

//int main() {
//    Vector v1;
//    Vector v2(3.0, 4.0);
//    v1.setX(6.0);
//    v1.setY(8.0);
//
//    std::cout << "p1 = (" << v1.getX() << ", " << v1.getY() << ")\n";
//    std::cout << "dist(p1) = " << v1.dist() << "\n";
//
//    std::cout << "p2 = (" << v2.getX() << ", " << v2.getY() << ")\n";
//    std::cout << "dist(p2) = " << v2.dist() << "\n";
//
//    Vector v3 = v1 + v2;
//    std::cout << "v3 id = " << v3.getID() << "\n\n";
//
//    double dot = v1 * v2;
//    std::cout << "v1 * v2 = " << dot << "\n\n";
//    std::cout << "distTo(v1, v2) = " << v1.distTo(v2) << "\n\n";
//
//    return 0;
//}

//#include <iostream>
//#include "Point3D.h"
//#include "Point2D.h"
//
//int main() {
//    std::cout << "=== Test Point3D ===\n";
//    Point3D p3(1.0, 2.0, 3.0);
//
//    std::cout << "p3 = (" << p3.getX() << ", " << p3.getY() << ", " << p3.getZ() << ")\n";
//    std::cout << "dist(p3) = " << p3.dist() << "\n\n";
//
//
//    std::cout << "=== Test Point2D inheritance ===\n";
//    Point2D p2(4.0, 5.0);
//
//
//    std::cout << "p2 = (" << p2.getX() << ", " << p2.getY() << ")\n";
//
//
//    p2.setX(10.0);
//    p2.setY(20.0);
//    std::cout << "after set: p2 = (" << p2.getX() << ", " << p2.getY() << ")\n";
//
//    std::cout << "dist(p2) = " << p2.dist() << "\n";
//
//
//    std::cout << "\n=== Check that z is hidden in Point2D ===\n";
//
//
//     //p2.setZ(7.0);
//
//
//
//    return 0;
//}

#include <iostream>
#include "Vector.h"
#include "VectorCollection.h"

int main() {
    VectorCollection col;

    std::cout << "=== Add vectors ===\n";
    col.addVector(Vector(3, 4));   // dist = 5
    col.addVector(Vector(1, 1));   // dist = sqrt(2)
    col.addVector(Vector(6, 8));   // dist = 10
    col.addVector(Vector(-2, 0));  // dist = 2


    for (int i = 0; i < 4; i++) {
        Vector v = col.getVector(i);
        std::cout << i << ": (" << v.getX() << ", " << v.getY()
                  << ") dist=" << v.dist()
                  << " id=" << v.getID() << "\n";
    }

    std::cout << "\n=== Sort by distance ===\n";
    col.sortByDistance();

    for (int i = 0; i < 4; i++) {
        Vector v = col.getVector(i);
        std::cout << i << ": (" << v.getX() << ", " << v.getY()
                  << ") dist=" << v.dist() << "\n";
    }

    std::cout << "\n=== Add sum of vectors 0 and 1 to collection ===\n";
    col.addSumByIndex(0, 1);


    for (int i = 0; i < 5; i++) {
        Vector v = col.getVector(i);
        std::cout << i << ": (" << v.getX() << ", " << v.getY()
                  << ") dist=" << v.dist() << "\n";
    }

    std::cout << "\n=== Total vector of collection ===\n";
    Vector total = col.totalVector();
    std::cout << "total = (" << total.getX() << ", " << total.getY()
              << ") dist=" << total.dist() << "\n";

    return 0;
}


