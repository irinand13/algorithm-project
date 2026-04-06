//
// Created by iraan on 06.04.2026.
//
#pragma once
#include <Array.h>

#ifndef ARRAYSORT_H
#define ARRAYSORT_H
namespace ArraySort {

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
            int index = (arr[i] - min) * bucketCount / (max - min);
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
    void quickSort (Array<T>& arr) {

    }
    template<typename T>
    void shellSort(Array<T>& arr) {

    }
}

#endif //ARRAYSORT_H
