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
    typename SinglyLinkedList<T>::Node*
    Node* quickSort(SinglyLinkedList<T>& list, PivotType pivotType) {

        typename SinglyLinkedList<T>::Node* head = list.getHead();

        if (!head || !head->next) return head;
        int size = list.getSize();

        typename SinglyLinkedList<T>::Node* pivotNode =head;
        switch (pivotType) {

            case PivotType::MIDDLE: {
                for (int i = 0; i < size/2; i++)
                    pivotNode = pivotNode->next;

                break;
            }

            case PivotType::RANDOM: {
                for (int i = 0; i < rand() % size ; i++) {
                    pivotNode = pivotNode->next;
                }
                break;
            }

            case PivotType::EXTREME: {
                while (pivotNode->next)
                    pivotNode = pivotNode->next;
                break;
            }
        }
        T pivot = pivotNode->data;


        return head;
    }
}
#endif //SINGLYLISTSORT_H
