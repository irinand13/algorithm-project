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
    SinglyLinkedList<T> pushSorted(SinglyLinkedList<T> *newNode, SinglyLinkedList<T> *sortedList) {
        if (sortedList == nullptr || newNode->value <= sortedList->value) {
            newNode->next = sortedList;
            sortedList = newNode;
        }else {
            SinglyLinkedList<T> *current = sortedList;
            while (current->next != nullptr && current->next->value <= newNode->value) {current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        return sortedList;
    }

    template<class T>
    void insertionSort(SinglyLinkedList<T>& list) {
        if (list.getSize() <= 1) return;

        SinglyLinkedList<T> sortedList;
        for (int i = 0; i < list.getSize(); i++) {
            T value = list.get(i);
        }
        SinglyLinkedList<T> *current = list.getHead();

        while (current != nullptr) {
            SinglyLinkedList<T> *next = current->next;
            sortedList = pushSorted(current, sortedList);
            current = next;
        }
        list = sortedList;
    }


    template<class T>
    void bucketSort(SinglyListSort<T>& singlyList, int bucketCount) {
        int size = singlyList.getSize();
        T max = singlyList.findMax();
        T min = singlyList.findMin();

        SinglyLinkedList<T>* buckets= new SinglyLinkedList<T>[bucketCount];

        for (int i = 0; i < size; i++) {
            T value = singlyList.get(i);
        }

    }

    template<class T>
    void quickSort(SinglyListSort<T>& singlyList, int first, int last, PivotType pivotType) {

    }
}
#endif //SINGLYLISTSORT_H
