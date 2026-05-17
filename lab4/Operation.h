#ifndef LAB4_OPERATION_H
#define LAB4_OPERATION_H

enum OperationType{
    APPEND,
    INSERT,
    REMOVE
};

template<class T>
class Operation{
public:
    OperationType type;
    T item;
    int index;

    Operation(OperationType type, T item, int index=-1){
        this->type = type;
        this->item = item;
        this->index = index;
    };
};


#endif //LAB4_OPERATION_H
