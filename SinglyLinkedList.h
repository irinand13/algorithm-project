//
// Created by iraan on 20.03.2026.
//
// Dynamiczna lista jednokierunkowa,  która jest inicjalizowana jako szablon
template<class T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node *next;
    };
    Node *head;

public:
    void SinglyLinkedList () {
        head = nullptr;
    }

};
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#endif //SINGLYLINKEDLIST_H
