#ifndef LAB4_LAZYSEQUENCE_H
#define LAB4_LAZYSEQUENCE_H

#include <stdexcept>

#include "Sequence.h"
#include "DynamicArray.h"
#include "Generator.h"
#include "MutableArraySequence.h"
#include "Cardinal.h"
#include "Operation.h"

template<class T>
class LazySequence : public Sequence<T>{
protected:
    Sequence<T>* materialized;
    Generator<T>* generator;
    Sequence<Operation<T>>* operation;

public:
    LazySequence(){
        this->materialized = new MutableArraySequence<T>(new DynamicArray<T> (0));
        this->generator = nullptr;
        this->operation = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (T* items, int count){
        this->materialized = new MutableArraySequence<T>(new DynamicArray<T> (items, count));
        this->generator = nullptr;
        this->operation = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));    };

    LazySequence (Sequence<T>* seq){
        this->materialized = seq;
        this->generator = nullptr;
        this->operation = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (T(*func)(Sequence<T>*), Sequence<T>* seq) {
        this->generator = new Generator<T>(func, this);
        this->materialized = seq;
        this->operation = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (std::function<T(Sequence<T>*)> func, Sequence<T>* seq){
        this->generator = new Generator<T>(func, this);
        this->materialized = seq;
        this->operation = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (const LazySequence<T>& list){
        this->materialized = new MutableArraySequence<T>(new DynamicArray<T>(0));

        for(int i = 0; i < list.materialized->GetLength(); i++){
            this->materialized->Append(list.materialized->Get(i));
        }

        if(list.generator != nullptr){
            this->generator = new Generator<T>(list.generator->GetFunction(), this);
        }
        else{
            this->generator = nullptr;
        }
        this->operation = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    void GenerateNext(){
        materialized->Append(generator->GetNext());
    }

    T GetFirst() override{
        if(materialized->GetLength() == 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        return materialized->GetFirst();
    };

    T GetLast() override{
        if(materialized->GetLength() == 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        while(generator != nullptr){
            GenerateNext();
        }

        return materialized->GetLast();
    };

    T Get(int index) override{
        if(index < 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        while(materialized->GetLength() <= index){
            if(generator == nullptr){
                throw std::out_of_range("IndexOutOfRange");
            }

            GenerateNext();
        }

        return materialized->Get(index);
    };

    LazySequence<T>* GetSubsequence(int startIndex, int endIndex) override{
        if(startIndex < 0 || endIndex < startIndex){
            throw std::out_of_range("IndexOutOfRange");
        }

        while(materialized->GetLength() <= endIndex){
            if(generator == nullptr){
                throw std::out_of_range("IndexOutOfRange");
            }

            GenerateNext();
        }

        Sequence<T>* sub = materialized->GetSubsequence(startIndex, endIndex);
        return new LazySequence<T>(sub);
    };

    Cardinal GetLength() const{
        if(generator != nullptr){
            return Cardinal(0, true);
        }

        return Cardinal(materialized->GetLength(), false);
    };

    size_t GetMaterializedCount() const{
        return materialized->GetLength();
    };

    Sequence<T>* Append(T item) override{
        operation->Append(Operation<T>(APPEND, item));
        return this;
    };

    Sequence<T>* Prepend(T item) override{
        operation->Append(Operation<T>(INSERT, item, 0));
        return this;
    };

    Sequence<T>* InsertAt(T item, int index) override{
        if(index < 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        operation->Append(Operation<T>(INSERT, item, index)
        );

        return this;
    };






};
#endif //LAB4_LAZYSEQUENCE_H
