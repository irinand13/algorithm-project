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
    void quickSort(SinglyLinkedList<T>& list, PivotType pivotType) {
        typename SinglyLinkedList<T>::Node* head = list.getHead();
        int size = list.getSize();

        if (!head || !head->next) return;

        typename SinglyLinkedList<T>::Node* pivotNode =nullptr;
        switch (pivotType) {

            case PivotType::MIDDLE: {
                int pivotPosition = size / 2;
                pivotNode = head;

                for (int i = 0; i < pivotPosition; i++)
                    pivotNode = pivotNode->next;

                break;
            }

            case PivotType::RANDOM: {
                int pivotPosition = rand() % size;
                pivotNode = head;

                for (int i = 0; i < pivotPosition; i++)
                    pivotNode = pivotNode->next;

                break;
            }

            case PivotType::EXTREME: {
                pivotNode = head;
                while (pivotNode->next)
                    pivotNode = pivotNode->next;

                break;
            }
        }
        T pivot = pivotNode->data;
    }
}
#endif //SINGLYLISTSORT_H
