//
// Created by iraan on 06.04.2026.
//
#pragma once
#include <Array.h>
#include "Types.h"
#include <cstdlib>
#include <ctime>

#ifndef ARRAYSORT_H
#define ARRAYSORT_H
namespace ArraySort {
    /**
     * Sortowanie przez wstawianie
     * Przesuwa element w lewo, dopóki nie napotka się
     * na element mniejszy lub początek tablicy
     * @tparam T szablon typu danych
     * @param arr wskażnik na tablice
     * @param size rozmiar tablicy
     */
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
    void busketSort(Array<T>& arr, int bucketCount) {
        int size = arr.getSize();

        T max = arr.findMax();
        T min = arr.findMin();

        T** buckets = new T*[bucketCount];
        int* bucketSizes = new int[bucketCount];

        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = new T[size];
            bucketSizes[i] = 0;
        }

        for (int i = 0; i < size; i++) {
            int index = (arr[i] - min) * (bucketCount - 1) / (max - min);
            buckets[index][bucketSizes[index]] = arr[i];
            bucketSizes[index]++;
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
    void quickSort (Array<T>& arr, int first, int last, PivotType pivotType) {

        if (first >= last) return;

        int pivotPosition;
        T pivot;

        switch (pivotType) {
            case PivotType::MIDDLE :
                pivotPosition = (first + last) / 2;
                break;
            case PivotType::RANDOM :
                pivotPosition = rand() % (last - first + 1) + first;
                break;
            case PivotType::EXTREME :
                pivotPosition = last;
                break;
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

        quickSort(arr, first, i - 1, pivotType);
        quickSort(arr, i + 1, last, pivotType);
    }


    template<typename T>
    void shellSort(Array<T>& arr) {


    }

}

#endif //ARRAYSORT_H
