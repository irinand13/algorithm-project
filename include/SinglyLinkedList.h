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
    }
};

#endif //SINGLYLINKEDLIST_H
