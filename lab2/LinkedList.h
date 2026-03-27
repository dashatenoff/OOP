#include "stdexcept"
#ifndef UNTITLED2_LINKEDLIST_H
#define UNTITLED2_LINKEDLIST_H

template<class T>
struct Node{
    T data;
    Node<T> * next;
};

template<class T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    LinkedList (T* items, int count);
    LinkedList ();
    LinkedList (const LinkedList <T> & list);
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const;
    int GetLength() const;
    void Append(T item) ;
    void Prepend(T item) ;
    void InsertAt(T item, int index);
    LinkedList<T>* Concat(LinkedList<T> *list);
    ~ LinkedList<T>();
};

template<class T>
LinkedList<T> :: LinkedList(T* items, int count){
    if (count<0){
        throw std::invalid_argument("Count cannot be negative");
    }
    if (count == 0) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return;
    }
    else{
        this->size = count;
        Node<T>* prev = nullptr;
        Node<T>* curr = new Node<T>;
        this->head = curr;

        for (int i=0; i<count-1; i++){
            curr->data = items[i];
            prev = curr;
            curr = new Node<T>;
            prev->next = curr;
            curr->next = nullptr;
        }
        curr->data = items[count-1];
        this->tail = curr;
    }
}

template<class T>
LinkedList<T> :: LinkedList(){
    this->head=nullptr;
    this->tail=nullptr;
    this->size=0;
}

template<class T>
LinkedList<T> :: LinkedList(const LinkedList <T> & list){
    int count=list.size;
    if (count<0){
        throw std::invalid_argument("Count cannot be negative");
    }
    if (count == 0) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return;
    }
    else{
        this->size = count;
        Node<T>* prev = nullptr;
        Node<T>* curr = new Node<T>;
        this->head = curr;
        Node<T>* currIt = list.head;
        for (int i=0; i<count-1; i++){
            curr->data = currIt->data;
            prev = curr;
            curr = new Node<T>;
            prev->next = curr;
            curr->next = nullptr;
            currIt = currIt->next;
        }
        curr->data = currIt->data;
        this->tail = curr;
    }
}

template<class T>
T LinkedList<T> ::GetFirst() const{
    if (this->size==0){
        throw std::out_of_range("IndexOutOfRange");
    }
    return this->head->data;
}

template<class T>
T LinkedList<T> ::GetLast() const{
    if (this->size==0){
        throw std::out_of_range("IndexOutOfRange");
    }
    return this->tail->data;
}

template<class T>
T LinkedList<T> :: Get(int index) const{
    if (index<0 || index >= this->size){
        throw std::out_of_range("IndexOutOfRange");
    }
    Node<T>* curr = this->head;
    for (int i=0; i<index; i++){
        curr = curr->next;
    }
    return curr->data;
}

template<class T>
LinkedList<T>* LinkedList<T> :: GetSubList(int startIndex, int endIndex) const{
    if (startIndex<0 || startIndex >= this->size || endIndex<0 || endIndex >= this->size || startIndex>endIndex){
        throw std::out_of_range("IndexOutOfRange");
    }

    Node<T>* currIt = this->head;
    Node<T>* curr;

    for (int i=0; i<startIndex; i++){
        currIt = currIt->next;
    }

    LinkedList<T>* newList = new LinkedList<T>();
    curr = new Node<T>;
    newList->head = curr;
    curr->next = nullptr;

    int count = endIndex-startIndex+1;
    newList->size=count;
    Node<T>* prev = nullptr;

    for (int i=0; i<count-1; i++){
        curr->data = currIt->data;
        prev = curr;
        curr = new Node<T>;
        prev->next = curr;
        curr->next = nullptr;
        currIt = currIt->next;
    }
    curr->data = currIt->data;
    newList->tail = curr;
    return newList;
}

template<class T>
int LinkedList<T> ::GetLength() const{
    return this->size;
}

template<class T>
void LinkedList<T>::Append(T item) {
    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    newNode->next = nullptr;

    if (this->size == 0) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        this->tail = newNode;
    }

    this->size++;
}

template<class T>
void LinkedList<T>::Prepend(T item) {
    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    newNode->next = this->head;

    this->head = newNode;

    if (this->size == 0) {
        this->tail = newNode;
    }

    this->size++;
}

template<class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > this->size) {
        throw std::out_of_range("IndexOutOfRange");
    }
    if (index == 0) {
        Prepend(item);
        return;
    }
    if (index == this->size) {
        Append(item);
        return;
    }

    this->size++;
    Node<T>* curr = this->head;
    for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    newNode->next = curr->next;
    curr->next = newNode;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
    if (list->head == nullptr) {
        return this;
    }

    if (this->head == nullptr) {
        this->head = list->head;
        this->tail = list->tail;
        this->size = list->size;
        return this;
    }

    this->tail->next = list->head;
    this->tail = list->tail;
    this->size += list->size;

    return this;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

#endif //UNTITLED2_LINKEDLIST_H
