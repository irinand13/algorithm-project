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
    int size;
    public:

    //konstruktor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    };

    //destruktor
    ~DoublyLinkedList() {
        Node *current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    };

    void push(T d) {
        Node *newNode = new Node(d);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
};
#endif //DOUBLYLINKEDLIST_H
