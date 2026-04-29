#ifndef LAB3_QUEUE_H
#define LAB3_QUEUE_H

#include "Sequence.h"
#include "MutableListSequence.h"
#include "LinkedList.h"
#include "IEnumerator.h"
#include "ListEnumerator.h"
#include "Elements.h "

#include <stdexcept>
#include <string>

template<class T>
class Queue {
private:
    Sequence<T>* data;

public:
    Queue() {
        data = new MutableListSequence<T>(new LinkedList<T>());
    }

    Queue(Sequence<T>* seq) {
        data = seq;
    }

    ~Queue() {
        delete data;
    }

    int Size() const {
        return data->GetLength();
    }

    bool Empty() const {
        return Size() == 0;
    }

    void Enqueue(const T& value) {
        Sequence<T>* newData = data->Append(value);

        if(newData != data)
            delete data;

        data = newData;
    }

    T Front() const {
        if(Empty())
            throw std::out_of_range("Queue empty");

        return data->GetFirst();
    }

    T Dequeue() {
        if(Empty())
            throw std::out_of_range("Queue empty");

        T value = data->GetFirst();

        Sequence<T>* newData;

        if(Size() == 1)
            newData = new MutableListSequence<T>(new LinkedList<T>());
        else
            newData = data->GetSubsequence(1, Size()-1);

        delete data;
        data = newData;

        return value;
    }

    Queue<T>* Map(T (*func)(const T&)) const {
        Sequence<T>* newSeq = data->Map(func);
        return new Queue<T>(newSeq);
    }

    Queue<T>* Where(bool (*func)(const T&)) const {
        Sequence<T>* newSeq = data->Where(func);
        return new Queue<T>(newSeq);
    }

    T Reduce(T (*func)(const T&, const T&), const T& start) const{
        return data->Reduce(func, start);
    }

    void Concat(const Queue<T>& other){

        Sequence<T>* newData = data->Concat(other.data);

        if(newData != data)
            delete data;

        data = newData;
    }

    Queue<T>* Subsequence(int start, int end) const {

        Sequence<T>* newSeq = data->GetSubsequence(start,end);

        return new Queue<T>(newSeq);
    }

    int FindSubsequence(const Queue<T>& sub) const {

        int n = data->GetLength();
        int m = sub.data->GetLength();

        if(m ==0)
            return -1;

        for(int i = 0; i<=n-m; i++){
            bool ok = true;

            for(int j=0; j<m; j++) {
                if (data->Get(i + j) != sub.data->Get(j)) {
                    ok = false;
                    break;
                }
            }
                if(ok)
                    return i;
        }
       return -1;
    }

    void Split(bool (*predicate)(const T&), Queue<T>& q1, Queue<T>& q2) const {

        IEnumerator<T>* it = data->GetEnumerator();

        while(it->MoveNext()){
            T value = it->Current();

            if(predicate(value))
                q1.Enqueue(value);
            else
                q2.Enqueue(value);
        }

        delete it;
    }
};

#endif //LAB3_QUEUE_H
