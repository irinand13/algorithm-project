//
// Created by iraan on 06.04.2026.
//
#pragma once
#include <Array.h>
#include "Types.h"
#include "Parameters.h"
#include <cstdlib>
#include <ctime>

#ifndef ARRAYSORT_H
#define ARRAYSORT_H
namespace ArraySort {

    template<typename T>
    void insertionSort (Array<T>& arr, int size) {
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
    void quickSort (Array<T>& arr, int first, int last) {

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

        quickSort(arr, first, i - 1);
        quickSort(arr, i + 1, last);
    }


    template<typename T>
    void bucketSort(Array<T>& arr, int bucketCount, BucketInnerSort sortType) {
        int size = arr.getSize();
        T max = arr.findMax();
        T min = arr.findMin();

        auto** buckets = new Array<T>*[bucketCount];
        int* bucketSizes = new int[bucketCount];

        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = new Array<T>(size);
            bucketSizes[i] = 0;
        }


        for (int i = 0; i < size; i++) {

            int index = (bucketCount - 1) * (arr[i] - min) / (max - min);

            if (index < 0) index = 0;
            if (index >= bucketCount) index = bucketCount - 1;

            int pos = bucketSizes[index];
            (*buckets[index])[pos] = arr[i];
            bucketSizes[index]++;
        }


        for (int i = 0; i < bucketCount; i++) {

            if (bucketSizes[i] <= 1) continue;

            if (sortType == BucketInnerSort::insertion) {
                insertionSort(*buckets[i], bucketSizes[i]);
            }
            else {
                quickSort(*buckets[i], 0, bucketSizes[i] - 1);
            }
        }

        int k = 0;
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[k++] = (*buckets[i])[j];
            }
        }

        for (int i = 0; i < bucketCount; i++) {
            delete buckets[i];
        }
        delete[] buckets;
        delete[] bucketSizes;
    }




    template<typename T>
    void shellSort(Array<T>& arr) {


    }

}

#endif //ARRAYSORT_H
