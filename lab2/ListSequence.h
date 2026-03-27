#ifndef UNTITLED2_LISTSEQUENCE_H
#define UNTITLED2_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;

protected:
    virtual Sequence<T>* Instance() = 0;
    virtual Sequence<T>* Clone() const = 0;

public:
    ListSequence(LinkedList<T>* list) {
        items = list;
    }

    T GetFirst() const override {
        return items->GetFirst();
    }

    T GetLast() const override {
        return items->GetLast();
    }

    T Get(int index) const override {
        return items->Get(index);
    }

    int GetLength() const override {
        return items->GetLength();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        return new MutableListSequence<T>(items->GetSubList(startIndex, endIndex));
    }

protected:

    Sequence<T>* AppendImpl(T item) {
        items->Append(item);
        return this;
    }

    Sequence<T>* PrependImpl(T item) {
        items->Prepend(item);
        return this;
    }

    Sequence<T>* InsertAtImpl(T item, int index) {
        items->InsertAt(item, index);
        return this;
    }

    Sequence<T>* ConcatImpl(Sequence<T>* list) {
        int oldSize = items->GetSize();
        int addSize = list->GetLength();

        items->Resize(oldSize + addSize);

        for (int i = 0; i < addSize; i++) {
            items->Set(oldSize + i, list->Get(i));
        }
        return this;
    }

public:

    Sequence<T>* Append(T item) override {
        return Instance()->AppendImpl(item);
    }

    Sequence<T>* Prepend(T item) override {
        return Instance()->PrependImpl(item);
    }

    Sequence<T>* InsertAt(T item, int index) override {
        return Instance()->InsertAtImpl(item, index);
    }

    Sequence<T>* Concat(Sequence<T>* list) override {
        return Instance()->ConcatImpl(list);
    }

    ~ListSequence() {
        delete items;
    }

    Sequence<T>* Map(T (*func)(T)) override {
        Sequence<T>* result = new MutableListSequence<T>(new LinkedList<T>());

        for (int i = 0; i < this->GetLength(); i++) {
            result->Append(func(this->Get(i)));
        }

        return result;
    }

    Sequence<T>* Where(bool (*func)(T)) override {
        Sequence<T>* result = new MutableListSequence<T>(new LinkedList<T>());

        for (int i = 0; i < this->GetLength(); i++) {
            T value = this->Get(i);
            if (func(value)) {
                result->Append(value);
            }
        }

        return result;
    }

    T Reduce(T (*func)(T, T), T start) override {
        T result = start;

        for (int i = 0; i < this->GetLength(); i++) {
            result = func(this->Get(i), result);
        }

        return result;
    }
};

#endif