#ifndef UNTITLED2_IMMUTABLELISTSEQUENCE_H
#define UNTITLED2_IMMUTABLELISTSEQUENCE_H

#include "ListSequence.h"

template<class T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence(LinkedList<T>* list) : ListSequence<T>(list) {}

protected:
    Sequence<T>* Instance() override {
        return Clone();
    }

    Sequence<T>* Clone() const override {
        return new ImmutableListSequence<T>(new LinkedList<T>(*this->items));
    }
};

#endif