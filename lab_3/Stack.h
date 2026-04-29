#ifndef LAB3_STACK_H
#define LAB3_STACK_H

#include "Sequence.h"
#include "MutableListSequence.h"
#include "LinkedList.h"
#include "IEnumerator.h"
#include "Elements.h"
#include <stdexcept>
#include <string>


template<class T>
class Stack {

private:
    Sequence<T>* data;

public:

    Stack() {
        data = new MutableListSequence<T>(new LinkedList<T>());
    }

    Stack(Sequence<T>* seq) {
        data = seq;
    }

    ~Stack() {
        delete data;
    }

    int Size() const {
        return data->GetLength();
    }

    bool Empty() const {
        return Size() == 0;
    }

    void Push(const T& value) {

        Sequence<T>* newData = data->Append(value);

        if(newData != data)
            delete data;

        data = newData;
    }

    T Top() const {

        if(Size() == 0)
            throw std::out_of_range("Stack empty");

        return data->Get(Size()-1);
    }

    T Pop() {

        if(Size() == 0)
            throw std::out_of_range("Stack empty");

        T value = data->Get(Size()-1);

        Sequence<T>* newData;

        if(Size() == 1)
            newData = new MutableArraySequence<T>(new DynamicArray<T>(0));
        else
            newData = data->GetSubsequence(0, Size()-2);

        delete data;
        data = newData;

        return value;
    }

    Stack<T>* Map(T (*func)(const T&)) const {

        Sequence<T>* newSeq = data->Map(func);

        return new Stack<T>(newSeq);
    }

    Stack<T>* Where(bool (*func)(const T&)) const {

        Sequence<T>* newSeq = data->Where(func);

        return new Stack<T>(newSeq);
    }

    T Reduce(T (*func)(const T&, const T&), const T& start) const{
        return data->Reduce(func, start);
    }

    void Concat(const Stack<T>& other){

        Sequence<T>* newData = data->Concat(other.data);

        if(newData != data)
            delete data;

        data = newData;
    }

    Stack<T>* Subsequence(int start, int end) const {

        Sequence<T>* newSeq = data->GetSubsequence(start,end);

        return new Stack<T>(newSeq);
    }

    int FindSubsequence(const Stack<T>& sub) const {
        int n = data->GetLength();
        int m = sub.data->GetLength();

        if(m == 0)
            return -1;

        for(int i=0;i<=n-m;i++){
            bool ok=true;

            for(int j=0;j<m;j++){
                if(data->Get(i+j) != sub.data->Get(j)){
                    ok=false;
                    break;
                }
            }
            if(ok)
                return i;
        }
        return -1;
    }
};


#endif //LAB3_STACK_H
