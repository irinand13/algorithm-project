//
// Created by iraan on 07.04.2026.
//

#ifndef SINGLYLISTSORT_H
#define SINGLYLISTSORT_H
#include <list>
#include <vector>

#include "SinglyLinkedList.h"
#include "Types.h"
using namespace std;
namespace SinglyLinkedListSort {
    template<class T>
    void bucketSort(SinglyLinkedList<T>& singlyList, int bucketCount) {
        int size = singlyList.getSize();
        T max = singlyList.findMax();
        T min = singlyList.findMin();

        auto* buckets= new SinglyLinkedList<T>[bucketCount];

        for (int i = 0; i < size; i++) {
            T value = singlyList.get(i);
        }
    }

    template<class T>
    typename SinglyLinkedList<T>::Node* quickSortRecursive(typename SinglyLinkedList<T>::Node* head, int currentSize, PivotType pivotType) {
        using Node = typename SinglyLinkedList<T>::Node;

        if (!head || !head->next) {
            return head;
        }


        Node* pivotNode = head;
        if (pivotType == PivotType::MIDDLE) {
            for (int i = 0; i < currentSize / 2; i++) pivotNode = pivotNode->next;
        } else if (pivotType == PivotType::RANDOM) {
            int r = rand() % currentSize;
            for (int i = 0; i < r; i++) pivotNode = pivotNode->next;
        } else if (pivotType == PivotType::EXTREME) {
            while (pivotNode->next) pivotNode = pivotNode->next;
        }

        T pivotValue = pivotNode->data;


        Node *lessHead = nullptr, *equalHead = nullptr, *greaterHead = nullptr;
        int lessSize = 0, greaterSize = 0;

        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->next = nullptr;

            if ((current->data) < pivotValue) {
                current->next = lessHead;
                lessHead = current;
                lessSize++;
            } else if (current->data > pivotValue) {
                current->next = greaterHead;
                greaterHead = current;
                greaterSize++;
            } else {
                current->next = equalHead;
                equalHead = current;
            }
            current = next;
        }

        lessHead = quickSortRecursive<T>(lessHead, lessSize, pivotType);
        greaterHead = quickSortRecursive<T>(greaterHead, greaterSize, pivotType);


        Node* newHead = nullptr;
        Node* tail = nullptr;


        auto append = [&](Node* section) {
            if (!section) return;
            if (!newHead) {
                newHead = section;
            } else {
                tail->next = section;
            }
            tail = section;
            while (tail->next) tail = tail->next;
        };

        append(lessHead);
        append(equalHead);
        append(greaterHead);

        return newHead;
    }


    template<class T>
    void quickSort(SinglyLinkedList<T>& list, PivotType pivotType) {
        if (list.getSize() <= 1) return;

        list.head = quickSortRecursive<T>(list.head, list.size, pivotType);
    }
}

#endif //SINGLYLISTSORT_H
