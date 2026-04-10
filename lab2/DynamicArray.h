#include <stdexcept>
#include <algorithm>
#ifndef UNTITLED2_DYNAMICARRAY_H
#define UNTITLED2_DYNAMICARRAY_H

template <class T>
class DynamicArray{
private:
    T* data;
    int size;

public:
    DynamicArray(const T* items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T> & dynamicArray);
    T Get(int index) const;
    int GetSize() const;
    void Set(int index, const T& value);
    void Resize(int newSize);
    ~DynamicArray();
};

template<class T>
T DynamicArray<T>::Get(int index) const {
    if (index<0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    return this->data[index];
}

template<class T>
int DynamicArray<T>::GetSize() const {
    return this->size;
}

template<class T>
void DynamicArray<T>::Set(int index, const T& value) {
    if (index<0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    this->data[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(int newSize){
    if (newSize < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }

    T* newData = new T[newSize];
    for (int i = 0; i < std::min(this->size, newSize); i++) {
        newData[i] = data[i];
    }
    delete[] data;
    this->data = newData;
    this->size = newSize;
}

template<class T>
DynamicArray<T>::DynamicArray(const T* items, int count){
    if (count < 0) {
        throw std::invalid_argument("Count cannot be negative");
    }

    this->data = new T[count];
    this->size = count;
    for (int i = 0; i < count; i++){
        this->data[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }

    this->data = new T[size];
    this->size = size;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> & dynamicArray){
    int newSize = dynamicArray.size;
    this->data = new T[newSize];
    this->size = newSize;
    for (int i=0; i<newSize; i++){
        this->data[i] = dynamicArray.data[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray(){
    delete []data;
}

#endif