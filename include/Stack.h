//
// Created by iraan on 18.04.2026.
//

#ifndef STACK_H
#define STACK_H
#include "SinglyLinkedList.h"

template<typename T>
//Klasa stosu zaimplementowana na bazie listy jednokierunkowej
class Stack {
private:
    SinglyLinkedList<T> list{};
public:
    //wstawia wartość
    void push(T data) { list.push_front(data); }
    //zwraca wskaźnik na górną wartość
    T& top() { return list.getHead()->data; }
    //zwraca rozmiar
    int getSize() { return list.getSize(); }
    //sprawdza czy jest posortowana
    bool isSorted() { return list.isSorted(); }
    //Operator dostępu indeksowego
    T& operator[](int i) { return list[i]; }

    //usuwanie elementu
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
