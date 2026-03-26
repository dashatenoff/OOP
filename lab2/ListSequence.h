//
// Created by dasha on 16/03/2026.
//

#ifndef UNTITLED2_LISTSEQUENCE_H
#define UNTITLED2_LISTSEQUENCE_H

template <class T>
class ArraySequence : public Sequence<T>{
private:
    DynamicArray<T>* items;
public:
    T GetFirst() const override{
        return items->Get(0);
    }
    T GetLast() const override{
        return item
    }
    T Get(int index) const override{
        }
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override{
    int GetLength() const override{
    Sequence<T>* Append(T item) override{
    Sequence<T>*Prepend(T item) override{
    Sequence<T>*InsertAt(T item, int index) override{
    Sequence <T>* Concat(Sequence <T> *list) override{
    ~Sequence() = default;

#endif //UNTITLED2_LISTSEQUENCE_H
