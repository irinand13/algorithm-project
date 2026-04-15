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


        Node *lessHead = nullptr, *equalHead = nullptr, *greaterHead = nullptr;
        Node *lessTail = nullptr, *equalTail = nullptr, *greaterTail = nullptr;
        int lessSize = 0, greaterSize = 0;

        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            current->next = current->prev = nullptr;


            if((current->data) < pivotValue) {
                if (!lessHead) lessHead = lessTail = current;
                else {
                    lessTail->next = current;
                    current->prev = lessTail;
                    lessTail = current;
                }
                lessSize++;
            }else if (current->data > pivotValue) {
                if (!greaterHead) greaterHead = greaterTail = current;
                else {
                    greaterTail->next = current;
                    current->prev = greaterTail;
                    greaterTail = current;
                }
                greaterSize++;
            }else {
                if (!equalHead) {
                    equalHead = equalTail = current;
                } else {
                    equalTail->next = current;
                    current->prev = equalTail;
                    equalTail = current;
                }
            }

            current = next;
        }


        auto getTail = [](Node* n) -> Node* {
            if (!n) return nullptr;
            while (n->next) n = n->next;
            return n;
        };

        lessHead = quickSortRecursive<T>(lessHead, getTail(lessHead), lessSize);
        greaterHead = quickSortRecursive<T>(greaterHead, getTail(greaterHead), greaterSize);

        Node* newHead = nullptr;
        Node* newTail = nullptr;

        auto append = [&](Node* h, Node* t) {
            if (!h) return;

            if (!newHead) {
                newHead = h;
                newTail = t;
            } else {
                newTail->next = h;
                h->prev = newTail;
                newTail = t;
            }
        };


        append(lessHead, getTail(lessHead));
        append(equalHead, getTail(equalHead));
        append(greaterHead, getTail(greaterHead));
        return newHead;
    }

    template<typename T>
    void quickSort(DoublyLinkedList<T>& list) {
        if (list.getSize() <= 1) return;

        list.head = quickSortRecursive<T>(list.head, list.tail, list.size);
    }

    template<class T>
   void bucketSort(DoublyLinkedList<T>& list) {

        const int size = list.getSize();
        const int bucketCount = std::max(1, (int)sqrt(size));

        T max = list.findMax();
        T min = list.findMin();

        if (max == min) return;

        auto* buckets = new DoublyLinkedList<T>[bucketCount];

        using Node = typename DoublyLinkedList<T>::Node;

        Node* current = list.getHead();

        while (current) {
            int index = (current->data - min) * (bucketCount - 1) / (max - min);
            buckets[index].push_back(current->data);
            current = current->next;
        }

        list.clear();

        for (int i = 0; i < bucketCount; i++) {

            if (buckets[i].getSize() > 0)
                insertionSort(buckets[i]);

            Node* node = buckets[i].getHead();

            while (node) {
                list.push_back(node->data);
                node = node->next;
            }
        }

        delete[] buckets;
    }
}
#endif //DOUBLYLINKEDLISTSORT_H
