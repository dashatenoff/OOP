#ifndef LAB4_GENERATOR_H
#define LAB4_GENERATOR_H

#include "Sequence.h"
#include <functional>

template<class T>
class LazySequence;

template<class T>
class Generator {
private:
    std::function<T(Sequence<T>*)> fun;
    LazySequence <T>* owner;

public:
    Generator(std::function<T(Sequence<T>*)> fun, LazySequence<T>* owner){
        this->fun = fun;
        this->owner = owner;
    }

    T GetNext(){
        return fun(owner);
    }


};
#endif //LAB4_GENERATOR_H
