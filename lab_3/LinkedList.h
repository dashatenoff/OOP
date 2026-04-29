#include <stdexcept>

#ifndef UNTITLED2_LINKEDLIST_H
#define UNTITLED2_LINKEDLIST_H

template<class T>
struct Node{
    T data;
    Node<T>* next;
};

template<class T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList(const T* items, int count);
    LinkedList();
    LinkedList(const LinkedList<T>& list);

    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const;

    int GetLength() const;

    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, int index);

    LinkedList<T>* Concat(const LinkedList<T>* list);

    Node<T>* GetHead() const {
        return head;
    }

    ~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList(const T* items, int count){
    if (count < 0){
        throw std::invalid_argument("Count cannot be negative");
    }

    if (count == 0){
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }

    size = count;

    Node<T>* prev = nullptr;
    Node<T>* curr = new Node<T>;
    head = curr;

    for (int i = 0; i < count - 1; i++){
        curr->data = items[i];
        prev = curr;
        curr = new Node<T>;
        prev->next = curr;
    }

    curr->data = items[count - 1];
    curr->next = nullptr;
    tail = curr;
}

template<class T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){
    int count = list.size;

    if (count == 0){
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }

    size = count;

    Node<T>* prev = nullptr;
    Node<T>* curr = new Node<T>;
    head = curr;

    Node<T>* currIt = list.head;

    for (int i = 0; i < count - 1; i++){
        curr->data = currIt->data;

        prev = curr;
        curr = new Node<T>;

        prev->next = curr;
        curr->next = nullptr;

        currIt = currIt->next;
    }

    curr->data = currIt->data;
    tail = curr;
}

template<class T>
T LinkedList<T>::GetFirst() const{
    if (size == 0){
        throw std::out_of_range("IndexOutOfRange");
    }
    return head->data;
}

template<class T>
T LinkedList<T>::GetLast() const{
    if (size == 0){
        throw std::out_of_range("IndexOutOfRange");
    }
    return tail->data;
}

template<class T>
T LinkedList<T>::Get(int index) const{
    if (index < 0 || index >= size){
        throw std::out_of_range("IndexOutOfRange");
    }

    Node<T>* curr = head;

    for (int i = 0; i < index; i++){
        curr = curr->next;
    }

    return curr->data;
}

template<class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) const{
    if (startIndex < 0 || endIndex >= size || startIndex > endIndex){
        throw std::out_of_range("IndexOutOfRange");
    }

    Node<T>* currIt = head;

    for (int i = 0; i < startIndex; i++){
        currIt = currIt->next;
    }

    LinkedList<T>* newList = new LinkedList<T>();

    int count = endIndex - startIndex + 1;

    for (int i = 0; i < count; i++){
        newList->Append(currIt->data);
        currIt = currIt->next;
    }

    return newList;
}

template<class T>
int LinkedList<T>::GetLength() const{
    return size;
}

template<class T>
void LinkedList<T>::Append(const T& item){
    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    newNode->next = nullptr;

    if (size == 0){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

template<class T>
void LinkedList<T>::Prepend(const T& item){
    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    newNode->next = head;

    head = newNode;

    if (size == 0){
        tail = newNode;
    }

    size++;
}

template<class T>
void LinkedList<T>::InsertAt(const T& item, int index){
    if (index < 0 || index > size){
        throw std::out_of_range("IndexOutOfRange");
    }

    if (index == 0){
        Prepend(item);
        return;
    }

    if (index == size){
        Append(item);
        return;
    }

    Node<T>* curr = head;

    for (int i = 0; i < index - 1; i++){
        curr = curr->next;
    }

    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    newNode->next = curr->next;

    curr->next = newNode;

    size++;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T>* list){
    Node<T>* curr = list->head;

    while (curr != nullptr){
        Append(curr->data);
        curr = curr->next;
    }

    return this;
}

template<class T>
LinkedList<T>::~LinkedList(){
    Node<T>* current = head;

    while (current != nullptr){
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

#endif