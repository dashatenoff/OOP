#ifndef LAB2_VECTOR_H
#define LAB2_VECTOR_H

#include "ArraySequence.h"
#include "MutableArraySequence.h"
#include <cmath>
#include <iostream>

template<class T>
class Vector {
private:
    Sequence<T> *data;
    0
public:
    Vector() {
        data = new MutableArraySequence<T>(new DynamicArray<T>(0));
    }

    ~Vector() {
        delete data;
    }

    int Size() const {
        return data->GetLength();
    }

    void PushBack(T value) {
        data->Append(value);
    }

    void PopBack() {
        int size = data->GetLength();

        if (size == 0)
            throw std::out_of_range("Vector is empty");

        Sequence<T> *newData;

        if (size == 1) {
            newData = new MutableArraySequence<T>(new DynamicArray<T>(0));
        } else {
            newData = data->GetSubsequence(0, size - 2);
        }

        delete data;
        data = newData;
    }


    T Get(int index) {
        return data->Get(index);
    }

    void Set(int index, T value) {
        int size = data->GetLength();

        if (index < 0 || index >= size)
            throw std::out_of_range("IndexOutOfRange");

        Sequence<T> *newData;

        if (index == 0) {
            newData = new MutableArraySequence<T>(new DynamicArray<T>(0));
        } else {
            newData = data->GetSubsequence(0, index - 1);
        }

        newData->Append(value);

        if (index + 1 < size) {
            newData->Concat(data->GetSubsequence(index + 1, size - 1));
        }

        delete data;
        data = newData;
    }

    T operator[](int index) const {
        return data->Get(index);
    }

    Vector<T> operator+(const Vector<T> &other) const {

        if (Size() != other.Size())
            throw std::invalid_argument("Vector sizes must match");

        Vector<T> result;
        int size = data->GetLength();

        for (int i = 0; i < size; i++) {
            result.PushBack((*this)[i] + other[i]);
        }

        return result;
    }

    Vector<T> operator*(T scalar) const {
        Vector<T> result;

        for (int i = 0; i < Size(); i++) {
            result.PushBack((*this)[i] * scalar);
        }
        return result;
    }

    T Dot(const Vector<T> &other) const {
        if (Size() != other.Size())
            throw std::invalid_argument("Vector sizes must match");

        T sum = 0;

        for (int i = 0; i < Size(); i++) {
            sum += (*this)[i] * other[i];
        }

        return sum;
    }

    double Norm() const {
        double sum = 0;

        for (int i = 0; i < Size(); i++) {
            sum += (*this)[i] * (*this)[i];
        }

        return sqrt(sum);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector<T> &v) {

        os << "[";

        for (int i = 0; i < v.Size(); i++) {
            os << v[i];
            if (i != v.Size() - 1)
                os << ", ";
        }

        os << "]";
        return os;
    }
};

#endif //LAB2_VECTOR_H
