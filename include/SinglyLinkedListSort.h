//
// Created by iraan on 07.04.2026.
//

#ifndef SINGLYLISTSORT_H
#define SINGLYLISTSORT_H
#include <cmath>
#include "SinglyLinkedList.h"
#include "Parameters.h"

namespace SinglyLinkedListSort {

    template<class T>
    typename SinglyLinkedList<T>::Node*
    insertionSort(typename SinglyLinkedList<T>::Node* head)
    {
        using Node = typename SinglyLinkedList<T>::Node;

        if (!head || !head->next)
            return head;

        Node* sorted = nullptr;

        Node* current = head;

        while (current != nullptr){
            Node* next = current->next;
            current->next = nullptr;

            if (sorted == nullptr || current->data <= sorted->data){
                current->next = sorted;
                sorted = current;
            }else {
                Node* temp = sorted;

                while (temp->next && (temp->next->data) < current->data){
                    temp = temp->next;
                }

                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }

        return sorted;
    }

    template<class T>
    void insertionSort(SinglyLinkedList<T>& list){
        using Node = typename SinglyLinkedList<T>::Node;

        Node* newHead = insertionSort<T>(list.getHead());

        list.setHead(newHead);
    }

    template<class T>
    typename SinglyLinkedList<T>::Node* quickSortRecursive(typename SinglyLinkedList<T>::Node* head, int currentSize) {
        using Node = typename SinglyLinkedList<T>::Node;

        if (!head || !head->next) return head;

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
                while (pivotNode->next)
                    pivotNode = pivotNode->next;
            break;

            default:
                pivotNode = head;
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

        lessHead = quickSortRecursive<T>(lessHead, lessSize);
        greaterHead = quickSortRecursive<T>(greaterHead, greaterSize);


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
    void quickSort(SinglyLinkedList<T>& list) {
        if (list.getSize() <= 1) return;

        list.head = quickSortRecursive<T>(list.head, list.size);
    }

    template<class T>
    void bucketSort(SinglyLinkedList<T>& singlyList) {
        const int size = singlyList.getSize();
        const int bucketCount = std::max(1, static_cast<int>(sqrt(size)));
        T max = singlyList.findMax();
        T min = singlyList.findMin();

        if (max == min) return;

        auto* buckets= new SinglyLinkedList<T>[bucketCount];

        typename SinglyLinkedList<T>::Node* current  = singlyList.getHead();
        while (current != nullptr) {
            int bucketIndex = ((current->data)-min)*(bucketCount-1)/(max - min);
            buckets[bucketIndex].push(current->data);
            current = current->next;
        }

        singlyList = SinglyLinkedList<T>();
        for (int i = 0; i < bucketCount; i++) {
            if (buckets[i].getSize() > 0) {
                insertionSort(buckets[i]);
            }
            typename SinglyLinkedList<T>::Node* bucketNode= buckets[i].getHead();
            while (bucketNode != nullptr) {
                singlyList.push(bucketNode->data);
                bucketNode = bucketNode->next;
            }
        }
        delete[] buckets;
    }


    template<class T>
    void shellSort(SinglyLinkedList<T>& list) {
        using Node = typename SinglyLinkedList<T>::Node;

        const int size = list.getSize();
        Node* head = list.getHead();

        for (int gap = size / 2; gap > 0; gap /= 2) {

            for (int i = gap; i < size; i++) {

                Node* iNode = head;
                for (int j = 0; j < i; j++) iNode = iNode->next;
                T temp = iNode->data;

                int j = i;

                while (j >= gap) {

                    Node* jGapNode = head;
                    for (int k = 0; k < j - gap; k++)
                        jGapNode = jGapNode->next;

                    if (jGapNode->data <= temp)
                        break;

                    Node* jNode = jGapNode;
                    for (int k = 0; k < gap; k++)
                        jNode = jNode->next;

                    jNode->data = jGapNode->data;

                    j -= gap;
                }

                Node* insertNode = head;
                for (int k = 0; k < j; k++)
                    insertNode = insertNode->next;

                insertNode->data = temp;
            }
        }
    }
}

#endif //SINGLYLISTSORT_H
