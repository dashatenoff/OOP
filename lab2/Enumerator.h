#ifndef LAB2_ENUMERATOR_H
#define LAB2_ENUMERATOR_H

#include <stdexcept>

#include "Sequence.h"
#include "IEnumerator.h"

template<class T>
class Enumerator : public IEnumerator<T>{
private:
    Sequence<T>* seq;
    int index;

public:
    Enumerator(Sequence<T>* sequence){
        seq = sequence;
        index = -1;
    }

    bool MoveNext() override{
        index++;
        return index< seq->GetLength();
    }

    T Current() override{
        if(index < 0 || index >= seq->GetLength()){
            throw std::out_of_range("Enumerator out of range");
        }
        return seq->Get(index);
    }

    void Reset() override{
        index=-1;
    }
};


#endif //LAB2_ENUMERATOR_H
