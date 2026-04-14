//
// Created by iraan on 06.04.2026.
//
#pragma once
#include <Array.h>
#include "Parameters.h"
#include <cstdlib>
#include <cmath>

#include "SinglyLinkedListSort.h"

#ifndef ARRAYSORT_H
#define ARRAYSORT_H

namespace ArraySort {
    template<class T>
    void swap(T& a, T& b) noexcept {
        T temp = a;
        a = b;
        b = temp;
    }
    // metoda sortawania przez wstawianie
    template<typename T>
    void insertionSort (T* arr, int size) {
        for (int i = 1; i < size; i++) {
            T current = arr[i];
            int otherIndex = i ;
            while (otherIndex > 0 && arr[otherIndex-1] > current) {
                arr[otherIndex] = arr[otherIndex - 1];
                otherIndex--;
            }
            arr[otherIndex] = current;
        }
    }

    template<typename T>
    void quickSortRecursive(Array<T>& arr, int first, int last) {
        if (first >= last) return;

        int pivotPosition;
        T pivot;

        switch (Parameters::pivot) {
            case Parameters::Pivots::middle:
                pivotPosition = (first + last) / 2;
            break;

            case Parameters::Pivots::random:
                pivotPosition = rand() % (last - first + 1) + first;
            break;

            case Parameters::Pivots::left:
                pivotPosition = first;
            break;

            case Parameters::Pivots::right:
                pivotPosition = last;
            break;

            default:
                pivotPosition = last;
        }
        pivot = arr[pivotPosition];

        swap(arr[last], arr[pivotPosition]);

        int i = first;
        for (int j = first; j < last; j++) {
            if(arr[j] < pivot) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[last]);

        quickSortRecursive(arr, first, i - 1);
        quickSortRecursive(arr, i + 1, last);
    }


    template<typename T>
    void quickSort (Array<T>& arr) {
        if (arr.getSize() <= 1) return;
        quickSortRecursive(arr, 0, arr.getSize() - 1);
    }



    template<typename T>
    void bucketSort(Array<T>& arr) {
        const int size = arr.getSize();
        const int bucketCount = std::max (1, static_cast<int>(std::sqrt(size)));
        T max = arr.findMax();
        T min = arr.findMin();

        if (max == min) return;


        T** buckets = new T*[bucketCount];
        int* bucketSizes = new int[bucketCount];

        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = new T[size];
            bucketSizes[i] = 0;
        }

        for (int i = 0; i < size; i++) {
            int index = (arr[i] - min) * (bucketCount - 1) / (max - min);
            buckets[index][bucketSizes[index]] = arr[i];
            ++bucketSizes[index];
        }

        for (int i = 0; i < bucketCount; i++) {
            if (bucketSizes[i] != 0) {
                insertionSort(buckets[i], bucketSizes[i]);
            }
        }
        int k = 0;

        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[k++] = buckets[i][j];
            }
        }

        for (int i = 0; i < bucketCount; i++) {
            delete[] buckets[i];
        }

        delete[] bucketSizes;
        delete[] buckets;
    }




    template<typename T>
    void shellSort(Array<T>& arr) {
        const int size = arr.getSize();

        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                T temp = arr[i];

                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;
            }
        }
    }

}

#endif //ARRAYSORT_H
