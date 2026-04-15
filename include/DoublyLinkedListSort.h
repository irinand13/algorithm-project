//
// Created by iraan on 15.04.2026.
//
#include "DoublyLinkedList.h"
#ifndef DOUBLYLINKEDLISTSORT_H
#define DOUBLYLINKEDLISTSORT_H
namespace DoublyLinkedListSort {

    template<class T>
    typename DoublyLinkedList<T>::Node*
    insertionSort(typename DoublyLinkedList<T>::Node* head) {
        using Node = typename DoublyLinkedList<T>::Node;

        if (!head || !head->next)
            return head;

        Node* sorted = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next;

            if (sorted == nullptr || current->data <= sorted->data) {
                current->next = sorted;
                if (sorted != nullptr) sorted->prev = current;
                sorted = current;
                sorted->prev = nullptr;
            }else {
                Node* temp = sorted;

                while (temp->next && (temp->next->data) < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;

                if (temp->next != nullptr) temp->next->prev = current;

                temp->next = current;
                current->prev = temp;
            }
            current = next;
        }

        return sorted;
    }

    template<typename T>
    void insertionSort(DoublyLinkedList<T>& list) {
        using Node = typename DoublyLinkedList<T>::Node;

        Node* newHead = insertionSort<T>(list.getHead());
        list.setHead(newHead);

        Node* newTail = newHead;
        if (newTail) {
            while (newTail->next) newTail = newTail->next;
        }
        list.setTail(newTail);
    }


    template<typename T>
    typename DoublyLinkedList<T>::Node*
        quickSortRecursive(typename DoublyLinkedList<T>::Node* head, typename DoublyLinkedList<T>::Node* tail ,int currentSize) {
        using Node = typename DoublyLinkedList<T>::Node;
        if (!head || head == tail || currentSize <= 1 ) return head;
        Node* pivotNode = head;
        switch (Parameters::pivot) {

            case Parameters::Pivots::middle:
                for (int i = 0; i < currentSize / 2; i++)
                    pivotNode = pivotNode->next;
            break;

            case Parameters::Pivots::random: {
                int r = rand() % currentSize;
                for (int i = 0; i < r; i++)
                    pivotNode = pivotNode->next;
                break;
            }

            case Parameters::Pivots::left:
                pivotNode = head;
            break;

            case Parameters::Pivots::right:
                pivotNode = tail;
            break;

            default:
                pivotNode = head;
        }
        T pivotValue = pivotNode->data;

        return ;
    }
}
#endif //DOUBLYLINKEDLISTSORT_H
