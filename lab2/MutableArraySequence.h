
#ifndef LAB2_MUTABLEARRAYSEQUENCE_H
#define LAB2_MUTABLEARRAYSEQUENCE_H

template<class T>
class MutableArraySequence : public ArraySequence<T>{
public:
    using ArraySequence<T>::ArraySequence;

protected:
    Sequence<T>* Instance() override{
        return this;
    }

    Sequence<T>* Clone() const override {
        return new MutableArraySequence<T>(*this);
    }

};

#endif //LAB2_MUTABLEARRAYSEQUENCE_H
