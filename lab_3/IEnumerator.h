#ifndef LAB2_IENUMERATOR_H
#define LAB2_IENUMERATOR_H

template<class T>
class IEnumerator {
public:
    virtual bool MoveNext() = 0;
    virtual T Current() = 0;
    virtual void Reset() = 0;
    virtual ~IEnumerator() = default;
};

#endif //LAB2_IENUMERATOR_H
