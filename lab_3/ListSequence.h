#ifndef UNTITLED2_LISTSEQUENCE_H
#define UNTITLED2_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"
#include "IEnumerator.h"
#include "ListEnumerator.h"

template<class T>
class MutableListSequence;

template<class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* items;

    virtual ListSequence<T>* Instance() = 0;
    virtual ListSequence<T>* Clone() const = 0;

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
        return new MutableListSequence<T>(
                items->GetSubList(startIndex, endIndex)
        );
    }

protected:

    Sequence<T>* AppendImpl(const T& item) {
        items->Append(item);
        return this;
    }

    Sequence<T>* PrependImpl(const T& item) {
        items->Prepend(item);
        return this;
    }

    Sequence<T>* InsertAtImpl(const T& item, int index) {
        items->InsertAt(item, index);
        return this;
    }

    Sequence<T>* ConcatImpl(const Sequence<T>* list) {
        for (int i = 0; i < list->GetLength(); i++) {
            items->Append(list->Get(i));
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

    ~ListSequence() {
        delete items;
    }

    Sequence<T>* Map(T (*func)(const T&)) override {
        Sequence<T>* result =
                new MutableListSequence<T>(new LinkedList<T>());

        for (int i = 0; i < this->GetLength(); i++) {
            result->Append(func(this->Get(i)));
        }

        return result;
    }

    Sequence<T>* Where(bool (*func)(const T&)) override {
        Sequence<T>* result =
                new MutableListSequence<T>(new LinkedList<T>());

        for (int i = 0; i < this->GetLength(); i++) {
            T value = this->Get(i);

            if (func(value)) {
                result->Append(value);
            }
        }

        return result;
    }

    T Reduce(T (*func)(const T&, const T&), const T& start) override {
        T result = start;

        for (int i = 0; i < this->GetLength(); i++) {
            result = func(this->Get(i), result);
        }

        return result;
    }

    IEnumerator<T>* GetEnumerator() override {
        return new ListEnumerator<T>(items->GetHead());
    }
};

#endif