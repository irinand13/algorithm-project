//
// Created by iraan on 06.04.2026.
//
#pragma once
#include <Array.h>

#include "Types.h"

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
        for (int i = 0; i < size; i++) {
            T temp = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > temp) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
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

        T pivot;
        int p  = first - 1 ;
        int q  = last + 1;
        switch (pivotType) {
            case PivotType::MIDDLE :pivot = arr[(first + last) / 2]; break;
            case PivotType::RANDOM : pivot = arr[rand() % (last - first + 1) + first]; break;
            case PivotType::EXTREME : pivot = arr[last]; break;
        }


        while (true) {
            while (arr[++p] < pivot)
                ;
            while (arr[--q] > pivot)
                ;

            if (p >= q) break;
            T temp = arr[p];
            arr[p] = arr[q];
            arr[q] = temp;

        }

        if (q > first) quickSort(arr, first, q, pivotType);
        if (q < last) quickSort(arr, q + 1, last, pivotType);
    }


    template<typename T>
    void shellSort(Array<T>& arr) {


    }
}

#endif //ARRAYSORT_H
