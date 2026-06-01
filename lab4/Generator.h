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
    Sequence<T>* materialized;

public:
    Generator(std::function<T(Sequence<T>*)> fun, Sequence<T>* materialized){
        this->fun = fun;
        this->materialized = materialized;
    }

    T GetNext(){
        return fun(materialized);
    }

    std::function<T(Sequence<T>*)> GetFunction() const{
        return fun;
    }
};


#endif //LAB4_GENERATOR_H
