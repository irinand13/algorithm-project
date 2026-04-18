//
// Created by iraan on 18.04.2026.
//

#ifndef STACK_H
#define STACK_H
#include "SinglyLinkedList.h"

template<typename T>
class Stack {
private:
    SinglyLinkedList<T> list{};
public:
    void push(T data) { list.push_front(data); }
    T& top() { return list.getHead()->data; }
    int getSize() { return list.getSize(); }
    bool isSorted() { return list.isSorted(); }
    T& operator[](int i) { return list[i]; }

    void pop() {
        if (list.getHead() != nullptr) {
            typename SinglyLinkedList<T>::Node* temp = list.getHead();
            list.setHead(temp->next);
            delete temp;
            list.size--;
        }
    }
    
};
#endif //STACK_H
