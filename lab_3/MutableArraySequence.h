#ifndef UNTITLED2_MUTABLEARRAYSEQUENCE_H
#define UNTITLED2_MUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"

template<class T>
class MutableArraySequence : public ArraySequence<T> {
public:

    MutableArraySequence(DynamicArray<T>* arr)
            : ArraySequence<T>(arr) {}

protected:

    ArraySequence<T>* Instance() override {
        return this;
    }

    ArraySequence<T>* Clone() const override {
        return new MutableArraySequence<T>(
                new DynamicArray<T>(*this->items)
        );
    }
};

#endif