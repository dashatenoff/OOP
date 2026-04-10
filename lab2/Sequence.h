#ifndef UNTITLED2_SEQUENCE_H
#define UNTITLED2_SEQUENCE_H

#include "IEnumerator.h"

template<class T>
class Sequence{
public:
    virtual T GetFirst() const  = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;

    virtual Sequence<T>* Concat(const Sequence<T>* list) = 0;

    virtual Sequence<T>* Map(T (*func)(const T&)) = 0;
    virtual Sequence<T>* Where(bool (*func)(const T&)) = 0;
    virtual T Reduce(T (*func)(const T&, const T&), const T& start) = 0;

    virtual IEnumerator<T>* GetEnumerator() = 0;

    virtual ~Sequence() = default;
};

#endif