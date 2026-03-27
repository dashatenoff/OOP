
#ifndef LAB2_IMMUTABLEARRAYSEQUENCE_H
#define LAB2_IMMUTABLEARRAYSEQUENCE_H

template <class T>
class ImmutableArraySequence : public ArraySequence<T>{
public:
    using ArraySequence<T>::ArraySequence;

protected:
    Sequence<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }

    Sequence<T>* Instance() override {
        return this->Clone();
    }
};

#endif //LAB2_IMMUTABLEARRAYSEQUENCE_H
