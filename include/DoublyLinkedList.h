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

        Node(T d) {
            data = d;
            next = nullptr;
            prev = nullptr;
        };
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
        head = nullptr;
        tail = nullptr;
        size = 0;
    };

    DoublyLinkedList(const DoublyLinkedList &other) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node *current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList &other) {
        if (this != &other) return *this;
        Node *current = other.head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
        Node* temp = other.head;
        while (temp != nullptr) {
            push_back(temp->data);
            temp = temp->next;
        }
        return *this;
    }


    void push_back(T d) {
        Node *newNode = new Node(d);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void read() {
        cout << "DoublyLinkedList::read()" << endl;
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
            cout << endl;
        }
    }

    int getSize () {
        return size;
    }
};
#endif //DOUBLYLINKEDLIST_H
