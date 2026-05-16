#include <vector>
#include <algorithm>
#include <iostream>
#include "Vector.h"
#include <ranges>

#ifndef UNTITLED2_VECTORCOLLECTION_H
#define UNTITLED2_VECTORCOLLECTION_H

class VectorCollection {
public:
    VectorCollection() {}

    void addVector(const Vector& v) {
        vectors.push_back(v);
    }

    static bool compareByDist(const Vector& a, const Vector& b) {
        return a.dist() < b.dist();
    }

    void sortByDistance() {
        std::sort(vectors.begin(), vectors.end(), compareByDist);
    }


    void addSumByIndex(int i, int j) {
        Vector sum = vectors[i] + vectors[j];
        vectors.push_back(sum);
    }

    Vector totalVector() const {
        Vector total(0.0, 0.0);
        for (int i = 0; i < (int)vectors.size(); i++) {
            total = total + vectors[i];
        }
        return total;
    }



    Vector getVector(int i) const {
        return vectors[i];
    }


private:
    std::vector<Vector> vectors;
};

#endif // UNTITLED2_VECTORCOLLECTION_H
