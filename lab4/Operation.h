#ifndef LAB4_OPERATION_H
#define LAB4_OPERATION_H

#include "Sequence.h"

enum OperationType{
    APPEND,
    INSERT,
    CONCAT
};

template<class T>
class Operation{
public:
    OperationType type;
    T item;
    int index;
    Sequence<T>* sequence;

    Operation(){
        type = APPEND;
        item = T();
        index = -1;
        sequence = nullptr;
    }

    Operation(OperationType type, T item, int index = -1){
        this->type = type;
        this->item = item;
        this->index = index;
        this->sequence = nullptr;
    };

    Operation(OperationType type, Sequence<T>* sequence){
        this->type = type;
        this->item = T();
        this->sequence = sequence;
        this->index = -1;
    };

    Operation(OperationType type, Sequence<T>* sequence, int index){
        this->type = type;
        this->item = T();
        this->sequence = sequence;
        this->index = index;
    };
};


#endif //LAB4_OPERATION_H
