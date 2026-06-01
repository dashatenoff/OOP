#ifndef UNTITLED2_SEQUENCE_H
#define UNTITLED2_SEQUENCE_H

#include "IEnumerator.h"
#include "Cardinal.h"

template<class T>
class Sequence{
public:
    virtual T GetFirst()  = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
    virtual Cardinal GetLength() = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(const T& item, int index) = 0;

    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual Sequence<T>* Map(T (*func)(const T&)) = 0;
    virtual Sequence<T>* Where(bool (*func)(const T&)) = 0;
    virtual T Reduce(T (*func)(const T&, const T&), const T& start) = 0;

    virtual IEnumerator<T>* GetEnumerator() = 0;

    virtual void Set(const T& item,int index) = 0;

    virtual ~Sequence() = default;
};

#endif