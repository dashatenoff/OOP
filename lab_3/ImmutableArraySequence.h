#ifndef UNTITLED2_IMMUTABLEARRAYSEQUENCE_H
#define UNTITLED2_IMMUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"

template<class T>
class ImmutableArraySequence : public ArraySequence<T>{
public:

    ImmutableArraySequence(DynamicArray<T>* arr) : ArraySequence<T>(arr) {}

protected:

    ArraySequence<T>* Instance() override {
        return Clone();
    }

    ArraySequence<T>* Clone() const override {
        return new ImmutableArraySequence<T>(
                new DynamicArray<T>(*this->items)
        );
    }
};

#endif