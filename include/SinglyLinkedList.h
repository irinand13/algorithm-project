//
// Created by iraan on 20.03.2026.
//
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

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
    SinglyLinkedList () {
        head = nullptr;
    }

    ~SinglyLinkedList () {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

};

#endif //SINGLYLINKEDLIST_H
