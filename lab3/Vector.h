#ifndef LAB2_VECTOR_H
#define LAB2_VECTOR_H

#include "ArraySequence.h"
#include "MutableArraySequence.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cassert>

template<class T>
class Vector {
private:
    Sequence<T> *data;

public:
    Vector() {
        data = new MutableArraySequence<T>(new DynamicArray<T>(0));
    }

    Vector(Sequence<T>* seq) {
        data = seq;
    }

    ~Vector() {
        delete data;
    }

    int Size() const {
        return data->GetLength();
    }

    void PushBack(const T& value) {
        Sequence<T>* newData = data->Append(value);
        if (newData != data)
            delete data;
        data = newData;
    }

    void PushFront(const T& value) {
        Sequence<T>* newData = data->Prepend(value);
        if (newData != data)
            delete data;
        data = newData;
    }

    void InsertAt(const T& value, int index) {
        Sequence<T>* newData = data->InsertAt(value, index);
        if (newData != data)
            delete data;
        data = newData;
    }

    void Concat(const Vector<T>* other) {
        Sequence<T>* newData = data->Concat(other->data);
        if (newData != data)
            delete data;
        data = newData;
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

    T Get(int index) const {
        return data->Get(index);
    }

    void Set(int index, const T& value) {
        int size = data->GetLength();

        if (index < 0 || index >= size)
            throw std::out_of_range("IndexOutOfRange");

        Sequence<T> *newData;

        if (index == 0) {
            newData = new MutableArraySequence<T>(new DynamicArray<T>(0));
        } else {
            newData = data->GetSubsequence(0, index - 1);
        }

        newData = newData->Append(value);

        if (index + 1 < size) {
            newData = newData->Concat(data->GetSubsequence(index + 1, size - 1));
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

        for (int i = 0; i < Size(); i++) {
            result.PushBack((*this)[i] + other[i]);
        }

        return result;
    }

    Vector<T> operator*(const T& scalar) const {
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

        return std::sqrt(sum);
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

    Vector<T>* Map(T (*func)(const T&)) const {
        Sequence<T>* newData = data->Map(func);
        return new Vector<T>(newData);
    }

    Vector<T>* Where(bool (*func)(const T&)) const {
        Sequence<T>* newData = data->Where(func);
        return new Vector<T>(newData);
    }

    T Reduce(T (*func)(const T&, const T&), const T& start) const {
        return data->Reduce(func,start);
    }

    IEnumerator<T>* GetEnumerator() const {
        return data->GetEnumerator();
    }

    static Vector<int>* Range(int l, int r){
        if (l > r)
            throw std::invalid_argument("Invalid range");

        Vector<int>* v = new Vector<int>();

        for (int i=l; i<=r; i++){
            v->PushBack(i);
        }

        return v;
    }

    static bool IsPrime(int x) {
        if (x<2) return false;

        for (int i=2; i*i <= x; i++){
            if (x%i == 0)
                return false;
        }

        return true;
    }

    static Vector<int>* PrimeNumbers(int l, int r) {
        Vector<int>* numbers = Range(l, r);
        Vector<int>* primes = numbers->Where(IsPrime);

        delete numbers;
        return primes;
    }

};

#endif