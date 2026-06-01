#ifndef LAB4_TAPE_H
#define LAB4_TAPE_H

#include <iostream>
#include "Sequence.h"
#include "MutableArraySequence.h"
#include "DynamicArray.h"

template<class T>
class Tape{
protected:
    Sequence<T>* data;
    int head;
    T blank;

public:
    Tape(T blankSymbol){
        data =
                new MutableArraySequence<T>(
                        new DynamicArray<T>(0)
                );

        blank = blankSymbol;
        head = 0;
        data->Append(blank);
    }

    Tape(
            Sequence<T>* seq,
            T blankSymbol
    ){
        data = seq;
        blank = blankSymbol;
        head = 0;

        if(data->GetLength().GetValue() == 0){
            data->Append(blank);
        }
    }

    T Read() const{
        return data->Get(head);
    }

    T Get(int index) const{
        return data->Get(index);
    }

    void Write(T item){
        data->Set(item, head);
    }

    void MoveLeft(){

        if(head == 0){
            data->Prepend(blank);
        }
        else{
            head--;
        }
    }

    void MoveRight(){

        head++;
        if(head >= data->GetLength().GetValue()){
            data->Append(blank);
        }
    }

    int GetHeadPosition() const{
        return head;
    }

    void Print() const{

        for(int i = 0; i < data->GetLength().GetValue(); i++){
            std::cout << data->Get(i) << " ";
        }

        std::cout << std::endl;

        for(int i = 0; i < head; i++){
            std::cout << "  ";
        }

        std::cout << "^" << std::endl;
    }
};

#endif //LAB4_TAPE_H