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

    // Metoda, która zamienia dwie wartości w tabeli miejscami
    template<class T>
    void swap(T& a, T& b) noexcept {
        T temp = a;
        a = b;
        b = temp;
    }

    // Metoda sortawania przez wstawianie
    //Dzieli tablicę na 2 części (posortowaną i nieposortowaną)
    // Wstawia element z części nie posortowanej w odpowiednie miejsce
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

    //Rekurencja do sortowania szybkiego
    //Dzieli tablice na 2 części(elementy większe i mniesze od pivota)
    template<typename T>
    void quickSortRecursive(Array<T>& arr, int first, int last, Parameters::Pivots pivotType) {
        if (first >= last) return;

        int pivotPosition;

        //wybór pivota
        switch (pivotType) {
            case Parameters::Pivots::middle:
                pivotPosition = (first + last) / 2; //ustawia miejsce środkowe
            break;

            case Parameters::Pivots::random:
                pivotPosition = rand() % (last - first + 1) + first; //ustawia losowe miejsce z zakresu od fisrt do last
            break;

            case Parameters::Pivots::left:
                pivotPosition = first; //ustawia na skrajnie lewy
            break;

            case Parameters::Pivots::right:
                pivotPosition = last; //ustawia na skrajny prawy
            break;

            default:
                pivotPosition = last;
        }

        std::swap(arr[pivotPosition], arr[last]); //zamiana pivota z ostatnim elementem
        T pivot = arr[last]; //wartość pivota

        int i = first; //granica między mniejszymi oraz większymi elementami

        //Pętla, która przchdzi przez każdy element i porównuje z wartością pivota
        for (int j = first; j < last; j++) {
            if (arr[j] < pivot) {
                std::swap(arr[i], arr[j]); //jeśli mniejsze od pivota, przesuń do lewej części
                i++;
            }
        }

        std::swap(arr[i], arr[last]);

        //wywołanie rekurencji dla tablic wynikowych
        quickSortRecursive(arr, first, i - 1, pivotType);
        quickSortRecursive(arr, i + 1, last, pivotType);
    }


    //Sortowanie szybkie
    //Wywoła metoda rekurencyjną quickSortRecursive
    template<typename T>
    void quickSort (Array<T>& arr,Parameters::Pivots pivotType) {
        if (arr.getSize() <= 1) return;
        quickSortRecursive(arr, 0, arr.getSize() - 1, pivotType);
    }

    // Ogólny szablon dla liczb
    //Normalizacja wartości
    //Przeszktałca na ułamek wartość z dowolnego przedziału liczbowego
    template<typename T>
    double getNormalizedValue(T value, T min, T max) {
        if (max == min) return 0.0;
        return static_cast<double>(value - min) / static_cast<double>(max - min);
    }

    // Obsługiwanie stringów dla podziału na kubełki w BucketSort
    // Oblicza przybliżoną pozycję elementu na podstawie wartości ASCII pierwszego znaku
    template<>
    inline double getNormalizedValue<std::string>(std::string value, std::string min, std::string max) {
        if (max == min) return 0.0;

        //pobieranie wartości ASCII z pierwszego znaku
        unsigned char v = value.empty() ? 0 : value[0];
        unsigned char mi = min.empty() ? 0 : min[0];
        unsigned char ma = max.empty() ? 0 : max[0];

        if (ma == mi) return 0.0;
        //zwraca proporcję znaku 'v' względem max i min
        return static_cast<double>(v - mi) / static_cast<double>(ma - mi);
    }

    //Sortowanie kubełkowe
    //Tworzy kubełki w których przechowywane są wartości oraz tablicę zawierającą rozmiary kubełków
    //Robi alokacje pamięci dla kubełków
    //Na podstawie wzoru rozdziela wartości do odpowiednich kubełków
    //Sortuje elementy wewnątrz kubełków
    template<typename T>
    void bucketSort(Array<T>& arr) {
        const int size = arr.getSize();
        const int bucketCount = std::max (1, static_cast<int>(std::sqrt(size)));
        T max = arr.findMax();
        T min = arr.findMin();

        if (max == min) return;


        T** buckets = new T*[bucketCount]; //tworzenie kubełków
        int* bucketSizes = new int[bucketCount];

        //inicjalizacja kubełków
        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = new T[size];
            bucketSizes[i] = 0;
        }

        //przypisywanie wartości do kubełków na podstawie ich wartości
        for (int i = 0; i < size; i++) {
            double norm = getNormalizedValue(arr[i], min, max);
            int index = static_cast<int>(norm * (bucketCount - 1));

            if (index < 0) index = 0;
            if (index >= bucketCount) index = bucketCount - 1;

            buckets[index][bucketSizes[index]] = arr[i];
            ++bucketSizes[index];
        }

        //wywołanie sortowania przez wstawianie w kubełkach
        for (int i = 0; i < bucketCount; i++) {
            if (bucketSizes[i] != 0) {
                insertionSort(buckets[i], bucketSizes[i]);
            }
        }
        int k = 0;

        //składanie posortowanych kubełków
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[k++] = buckets[i][j];
            }
        }

        for (int i = 0; i < bucketCount; i++) {
            delete[] buckets[i];
        }

        //usuwanie kubełków oraz tabeli rozmiarów
        delete[] bucketSizes;
        delete[] buckets;
    }


    //Sortowanie Shella
    //Porównuje elementy oddalone o konkretny odstęp
    //Ten odstęp zmiejsza się stopniowo w zależności od opcji wyboru gap
    template<typename T>
    void shellSort(Array<T>& arr, Parameters::ShellParameters shellParameter) {
        const int size = arr.getSize();

        //wybór opcji odstępu
        if(shellParameter == Parameters::ShellParameters::option1) {
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
        }else if(shellParameter == Parameters::ShellParameters::option2) {
            int gap = 1;

            while (gap < size / 3) {
                gap = 3 * gap + 1;
            }

            while (gap > 0) {

                for (int i = gap; i < size; i++) {

                    T temp = arr[i];
                    int j;

                    for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                        arr[j] = arr[j - gap];
                    }

                    arr[j] = temp;
                }

                gap /= 3;
            }

        }
    }

}

#endif //ARRAYSORT_H
