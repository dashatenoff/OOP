#ifndef LAB2_LISTENUMERATOR_H
#define LAB2_LISTENUMERATOR_H

#include "DynamicArray.h"
#include "LinkedList.h"
#include "IEnumerator.h"

#include <stdexcept>

template<class T>
class ListEnumerator : public IEnumerator<T>{
private:
    Node<T>* current;
    Node<T>* head;

public:
    ListEnumerator(Node<T>* start) {
        head = start;
        current = nullptr;
    }

    bool MoveNext() override {
        if (current == nullptr)
            current = head;
        else
            current = current->next;

        return current != nullptr;
    }

    T Current() override {
        if (!current)
            throw std::out_of_range("Out of range");
        return current->data;
    }

    void Reset() override {
        current = nullptr;
    }
};

#endif //LAB2_LISTENUMERATOR_H
