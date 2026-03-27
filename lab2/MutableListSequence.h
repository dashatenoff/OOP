#ifndef UNTITLED2_MUTABLELISTSEQUENCE_H
#define UNTITLED2_MUTABLELISTSEQUENCE_H

#include "ListSequence.h"

template<class T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence(LinkedList<T>* list) : ListSequence<T>(list) {}

protected:
    Sequence<T>* Instance() override {
        return this;
    }

    Sequence<T>* Clone() const override {
        return new MutableListSequence<T>(new LinkedList<T>(*this->items));
    }
};

#endif