//
// Created by iraan on 20.03.2026.
//
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#include <iterator>
#include <bits/range_access.h>
using namespace std;

// Dynamiczna lista jednokierunkowa,  która jest inicjalizowana jako szablon
template<class T>
class SinglyLinkedList {
private:
    struct Node  {
        T data;
        Node *next;

        //konstruktor węzła do przechowywania w liście
        Node(T d) {
            data = d;
            next = nullptr;
        }
    };

    Node *head;
    int size;

public:
    //konstruktor listy
    SinglyLinkedList () {
        head = nullptr;
        size = 0;
    }

    SinglyLinkedList (const SinglyLinkedList& other) {
        head = nullptr;
        size = 0;

        Node* current = other.head;

        while (current!=nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) return *this;

        Node* current = head;
        while (current!=nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;

        Node* temp = other.head;
        while (temp!=nullptr) {
            push(temp->data);
            temp = temp->next;
        }
        return *this;
    }



    //destruktor listy
    ~SinglyLinkedList () {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    //metoda która dodaje nową wartość do listy
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
        size++;
    }

    void read() {
        Node *current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            cout << endl;
            current = current->next;
        }
    }

    int getSize() {
        return size;
    }

    T findMin() const {
        if (head == nullptr) {
            cout << "The list is empty" << endl;
            return T();
        }
        T min = head->data;
        Node *current = head->next;
        while (current != nullptr) {
            if ((current->data) < min) {
                min = current->data;
            }
            current = current->next;
        }
        return min;
    }

    T findMax() const {
        if (head == nullptr) {
            cout << "The list is empty" << endl;
            return T();
        }
        T max = head->data;
        Node *current = head->next;
        while (current != nullptr) {
            if (current->data> max) {
                max = current->data;
            }
            current = current->next;
        }
        return max;
    }

    Node* getHead() {
        return head;
    }



};

#endif //SINGLYLINKEDLIST_H
