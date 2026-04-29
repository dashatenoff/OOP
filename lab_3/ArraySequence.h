#ifndef UNTITLED2_ARRAYSEQUENCE_H
#define UNTITLED2_ARRAYSEQUENCE_H

#include <stdexcept>
#include "IEnumerator.h"
#include "DynamicArray.h"
#include "Sequence.h"
#include "ArrayEnumerator.h"

template<class T>
class MutableArraySequence;

template<class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* items;

    virtual ArraySequence<T>* Instance() = 0;
    virtual ArraySequence<T>* Clone() const = 0;

public:
    ArraySequence(DynamicArray<T>* arr) {
        items = arr;
    }

    T GetFirst() const override {
        return items->Get(0);
    }

    T GetLast() const override {
        return items->Get(items->GetSize() - 1);
    }

    T Get(int index) const override {
        return items->Get(index);
    }

    int GetLength() const override {
        return items->GetSize();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex) {
            throw std::out_of_range("IndexOutOfRange");
        }

        int newSize = endIndex - startIndex + 1;

        DynamicArray<T>* newArr = new DynamicArray<T>(newSize);

        for (int i = 0; i < newSize; i++) {
            newArr->Set(i, items->Get(startIndex + i));
        }

        return new MutableArraySequence<T>(newArr);
    }

protected:

    Sequence<T>* AppendImpl(const T& item) {
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, item);
        return this;
    }

    Sequence<T>* PrependImpl(const T& item) {
        int oldSize = items->GetSize();

        items->Resize(oldSize + 1);

        for (int i = oldSize - 1; i >= 0; i--) {
            items->Set(i + 1, items->Get(i));
        }

        items->Set(0, item);

        return this;
    }

    Sequence<T>* InsertAtImpl(const T& item, int index) {
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

    Sequence<T>* ConcatImpl(const Sequence<T>* list) {
        int oldSize = items->GetSize();
        int addSize = list->GetLength();

        items->Resize(oldSize + addSize);

        for (int i = 0; i < addSize; i++) {
            items->Set(oldSize + i, list->Get(i));
        }

        return this;
    }

public:

    Sequence<T>* Append(const T& item) override {
        return Instance()->AppendImpl(item);
    }

    Sequence<T>* Prepend(const T& item) override {
        return Instance()->PrependImpl(item);
    }

    Sequence<T>* InsertAt(const T& item, int index) override {
        return Instance()->InsertAtImpl(item, index);
    }

    Sequence<T>* Concat(const Sequence<T>* list) override {
        return Instance()->ConcatImpl(list);
    }

    Sequence<T>* Map(T (*func)(const T&)) override {
        Sequence<T>* result =
                new MutableArraySequence<T>(new DynamicArray<T>(0));

        for (int i = 0; i < GetLength(); i++) {
            result->Append(func(Get(i)));
        }

        return result;
    }

    Sequence<T>* Where(bool (*func)(const T&)) override {
        Sequence<T>* result =
                new MutableArraySequence<T>(new DynamicArray<T>(0));

        for (int i = 0; i < GetLength(); i++) {
            T value = Get(i);

            if (func(value)) {
                result->Append(value);
            }
        }
        return result;
    }

    T Reduce(T (*func)(const T&, const T&), const T& start) override {
        T result = start;

        for (int i = 0; i < GetLength(); i++) {
            result = func(Get(i), result);
        }

        return result;
    }

    IEnumerator<T>* GetEnumerator() override {
        return new ArrayEnumerator<T>(items);
    }

    ~ArraySequence() {
        delete items;
    }
};

#endif