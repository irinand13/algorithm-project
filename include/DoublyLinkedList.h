//
// Created by iraan on 21.03.2026.
//

// Szablon listy dwukierunkowej
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


template<class T>
class DoublyLinkedList {
    private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    public:

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    };

    ~DoublyLinkedList() {
        Node *current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    };
};
#endif //DOUBLYLINKEDLIST_H
