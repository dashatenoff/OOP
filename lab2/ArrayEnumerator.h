#ifndef LAB2_ARRAYENUMERATOR_H
#define LAB2_ARRAYENUMERATOR_H

#include "DynamicArray.h"
#include "IEnumerator.h"

template<class T>
class ArrayEnumerator : public IEnumerator<T>{
private:
    const DynamicArray<T>* data;
    int index;

public:
    ArrayEnumerator(const DynamicArray<T>* arr) {
        data = arr;
        index = -1;
    }

    bool MoveNext() override {
        index++;
        return index < data->GetSize();
    }

    T Current() override {
        if(index < 0 || index >= data->GetSize())
            throw std::out_of_range("Out of range");
        return data->Get(index);
    }

    void Reset() override {
        index = -1;
    }
};

#endif //LAB2_ARRAYENUMERATOR_H
