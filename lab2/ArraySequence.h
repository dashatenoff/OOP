#include <stdexcept>
#include "DynamicArray.h"
#include "Sequence.h"

#ifndef UNTITLED2_ARRAYSEQUENCE_H
#define UNTITLED2_ARRAYSEQUENCE_H

template <class T>
class ArraySequence : public Sequence<T>{
private:
    DynamicArray<T>* items;
    virtual Sequence<T>* Inctance() = 0;
    virtual Sequense<T>* Clone() const= 0;
public:
    ArraySequence(DynamicArray<T>* arr){
    items = arr;
    }

    T GetFirst() const override{
        return items->Get(0);
    }

    T GetLast() const override{
        return items->Get(items->GetSize() - 1);
    }

    T Get(int index) const override{
        return items->Get(index);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override{
        if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
            throw std::out_of_range("IndexOutOfRange");

        int newSize = endIndex - startIndex + 1;
        DynamicArray<T>* newDynamicArray = new DynamicArray<T>(newSize);

        for (int i = 0; i < newSize; i++) {
            newDynamicArray->Set(i, items->Get(startIndex + i));
        }

        return new ArraySequence<T>(newDynamicArray);
    }

    int GetLength() const override{
        return items->GetSize();
    }

    Sequence<T>* Append(T item) override{
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        int oldSize = items->GetSize();
        items->Resize(oldSize + 1);

        for (int i = oldSize - 1; i >= 0; i--) {
            items->Set(i + 1, items->Get(i));
        }

        items->Set(0, item);
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        if (index < 0 || index > items->GetSize()) {
            throw std::out_of_range("IndexOutOfRange");
        }

        int oldSize = items->GetSize();
        items->Resize(oldSize + 1);

        for (int i = oldSize - 1; i >= index; i--) {
            items->Set(i + 1, items->Get(i));
        }

        items->Set(index, item);

        return this;
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        int oldSize = items->GetSize();
        int addSize = list->GetLength();
        items->Resize(oldSize + addSize);

        for (int i = 0; i < addSize; i++) {
            items->Set(oldSize + i, list->Get(i));
        }

        return this;
    }

    ~ArraySequence(){
        delete items;
    }
};
#endif //UNTITLED2_ARRAYSEQUENCE_H
