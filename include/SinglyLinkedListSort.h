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
namespace SinglyListSort {

    template<class T>
    void pushSorted(SinglyLinkedList<T> *newNode, SinglyLinkedList<T> *sortedList) {
        while (newNode != nullptr) {
            if (sortedList == nullptr || newNode->value <= sortedList->value) {
                newNode->next = sortedList;
                sortedList = newNode;
            }else {
                SinglyLinkedList<T> *current = sortedList;
                while (current->next != nullptr && current->next->value <= newNode->value) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }
    template<class T>
    void insertionSort(SinglyLinkedList<T>& list) {

    }


    template<class T>
    void bucketSort(SinglyListSort<T>& singlyList, int bucketCount) {

    }

    template<class T>
    void quickSort(SinglyListSort<T>& singlyList, int first, int last, PivotType pivotType) {

    }
}
#endif //SINGLYLISTSORT_H
