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
    Sequence<Operation<T>>* operations;

public:
    LazySequence(){
        this->materialized = new MutableArraySequence<T>(new DynamicArray<T> (0));
        this->generator = nullptr;
        this->operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (T* items, int count){
        this->materialized = new MutableArraySequence<T>(new DynamicArray<T> (items, count));
        this->generator = nullptr;
        this->operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));    };

    LazySequence (Sequence<T>* seq){
        this->materialized = seq;
        this->generator = nullptr;
        this->operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (T(*func)(Sequence<T>*), Sequence<T>* seq) {
        this->generator = new Generator<T>(func, seq);
        this->materialized = seq;
        this->operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (std::function<T(Sequence<T>*)> func, Sequence<T>* seq){
        this->generator = new Generator<T>(func, seq);
        this->materialized = seq;
        this->operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
    };

    LazySequence (const LazySequence<T>& list){
        this->materialized = new MutableArraySequence<T>(new DynamicArray<T>(0));

        for(int i = 0; i < list.materialized->GetLength().GetValue(); i++){
            this->materialized->Append(list.materialized->Get(i));
        }

        if(list.generator != nullptr){
            this->generator = new Generator<T>(list.generator->GetFunction(), this->materialized);
        }
        else{
            this->generator = nullptr;
        }

        this->operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));
        for(int i = 0; i < list.operations->GetLength().GetValue(); i++){
            this->operations->Append(list.operations->Get(i));
        }
    };

    ~LazySequence() override{
        delete materialized;
        delete generator;
        delete operations;
    }

    void GenerateNext(){

        if(generator == nullptr){
            throw std::out_of_range("No generator");
        }

        materialized->Append(generator->GetNext());
    }

    T GetFirst() override{
        return Get(0);
    }

    T GetLast() override{
        int opCount = operations->GetLength().GetValue();

        for(int i = opCount - 1; i >= 0; i--){
            Operation<T> op = operations->Get(i);

            if(op.type == APPEND){
                return op.item;
            }

            if(op.type == CONCAT){
                return op.sequence->GetLast();
            }
        }

        if(generator != nullptr){
            while(true){
                GenerateNext();
            }
        }

        int len = materialized->GetLength().GetValue();

        for(int i = 0; i < opCount; i++){
            Operation<T> op = operations->Get(i);

            if(op.type == INSERT){
                len++;
            }
        }

        if(len == 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        return Get(len - 1);
    }

      T Get(int index) override{
          if(index < 0){
              throw std::out_of_range("IndexOutOfRange");
          }

          int origIndex = index;
          int opCount = operations->GetLength().GetValue();

          for(int i = opCount - 1; i >= 0; i--){
              Operation<T> op = operations->Get(i);

              if(op.type == INSERT){
                  if(op.sequence != nullptr){
                      Cardinal seqLen = op.sequence->GetLength();
                      if(seqLen.IsInfinite()){
                          if(origIndex >= op.index)
                              return op.sequence->Get(origIndex - op.index);
                      } else {
                          int sLen = seqLen.GetValue();
                          if(origIndex >= op.index && origIndex < op.index + sLen)
                              return op.sequence->Get(origIndex - op.index);
                          if(origIndex >= op.index + sLen)
                              origIndex -= sLen;
                      }
                  } else {
                      if(op.index == origIndex){
                          return op.item;
                      }
                      if(op.index < origIndex){
                          origIndex--;
                      }
                  }
              }
          }

          while(materialized->GetLength().GetValue() <= origIndex){
              if(generator == nullptr){
                  int posInTail = origIndex - materialized->GetLength().GetValue();
                  int seenTail = 0;

                  for(int i = 0; i < opCount; i++){
                      Operation<T> op = operations->Get(i);

                      if(op.type == APPEND){
                          if(seenTail == posInTail){
                              return op.item;
                          }
                          seenTail++;
                      }

                      if(op.type == CONCAT){
                          int L = op.sequence->GetLength().GetValue();

                          if(posInTail < seenTail + L){
                              return op.sequence->Get(posInTail - seenTail);
                          }

                          seenTail += L;
                      }
                  }

                  throw std::out_of_range("IndexOutOfRange");
              }

              GenerateNext();
          }

          return materialized->Get(origIndex);
      }


    LazySequence<T>* GetSubsequence(int startIndex, int endIndex) override{
        if(startIndex < 0 || endIndex < startIndex){
            throw std::out_of_range("IndexOutOfRange");
        }

        Sequence<T>* sub = new MutableArraySequence<T>(new DynamicArray<T>(0));

        for(int i = startIndex; i <= endIndex; i++){
            sub->Append(this->Get(i));
        }

        return new LazySequence<T>(sub);
    }

    Cardinal GetLength() override{
        if(generator != nullptr){
            return Cardinal(0, true);
        }

        int opCount = operations->GetLength().GetValue();
        int extra = 0;

        for(int i = 0; i < opCount; i++){
            Operation<T> op = operations->Get(i);

            if(op.type == APPEND){
                extra++;
            }

            if(op.type == INSERT){
                if(op.sequence != nullptr){
                    Cardinal seqLen = op.sequence->GetLength();
                    if(seqLen.IsInfinite()) return Cardinal(0, true);
                    extra += seqLen.GetValue();
                } else {
                    extra++;
                }
            }

            if(op.type == CONCAT){
                Cardinal len = op.sequence->GetLength();

                if(len.IsInfinite()){
                    return Cardinal(0, true);
                }

                extra += len.GetValue();
            }
        }

        return Cardinal(materialized->GetLength().GetValue() + extra, false);
    }

    size_t GetMaterializedCount() const{
        return materialized->GetLength().GetValue();
    };

    Sequence<T>* Append(const T& item) override{
        operations->Append(Operation<T>(APPEND, item));
        return this;
    };

    Sequence<T>* Prepend(const T& item) override{
        operations->Append(Operation<T>(INSERT, item, 0));
        return this;
    };

    Sequence<T>* InsertAt(const T& item, int index) override{
        if(index < 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        Cardinal length = this->GetLength();
        if(!length.IsInfinite() && index > length.GetValue()){
            throw std::out_of_range("IndexOutOfRange");
        }

        operations->Append(Operation<T>(INSERT, item, index));

        return this;
    };

    Sequence<T>* InsertSequenceAt(Sequence<T>* seq, int index){
        if(index < 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        Cardinal length = this->GetLength();
        if(!length.IsInfinite() && index > (int)length.GetValue()){
            throw std::out_of_range("IndexOutOfRange");
        }

        operations->Append(Operation<T>(INSERT, seq, index));
        return this;
    }

    Sequence<T>* Concat(Sequence<T>* list) override{
        operations->Append(Operation<T>(CONCAT, list));

        return this;
    }

    Sequence<T>* Map(T (*func)(const T&)) override{
        return materialized->Map(func);
    }

    Sequence<T>* Where(bool (*func)(const T&)) override{
        return materialized->Where(func);
    }

    T Reduce(T (*func)(const T&, const T&), const T& start) override{
        return materialized->Reduce(func, start);
    }

    IEnumerator<T>* GetEnumerator() override{
        return materialized->GetEnumerator();
    }

    void Set(const T& item, int index) override{
        if(index < 0){
            throw std::out_of_range("IndexOutOfRange");
        }

        int opCount = operations->GetLength().GetValue();

        for(int i = 0; i < opCount; i++){
            Operation<T> op = operations->Get(i);

            if(op.type == APPEND){
                materialized->Append(op.item);
            }
            else if(op.type == INSERT){
                materialized->InsertAt(op.item, op.index);
            }
            else if(op.type == CONCAT){
                Cardinal L = op.sequence->GetLength();

                if(L.IsInfinite()){
                    throw std::logic_error("Set with pending infinite Concat is not supported");
                }

                int len = L.GetValue();
                for(int j = 0; j < len; j++){
                    materialized->Append(op.sequence->Get(j));
                }
            }
        }

        delete operations;
        operations = new MutableArraySequence<Operation<T>>(new DynamicArray<Operation<T>>(0));

        while(materialized->GetLength().GetValue() <= index){
            if(generator == nullptr){
                throw std::out_of_range("IndexOutOfRange");
            }

            GenerateNext();
        }

        materialized->Set(item, index);
    }

};
#endif //LAB4_LAZYSEQUENCE_H
