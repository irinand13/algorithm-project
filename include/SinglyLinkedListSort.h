//
// Created by iraan on 07.04.2026.
//

#ifndef SINGLYLISTSORT_H
#define SINGLYLISTSORT_H
#include <cmath>
#include "SinglyLinkedList.h"
#include "Parameters.h"

namespace SinglyLinkedListSort {

    // Metoda sortawania przez wstawianie
    //tworzy nowa posortowaną listę
    //wstawie do listy wartości w odpowidnie miejsce
    template<class T>
    typename SinglyLinkedList<T>::Node*
    insertionSort(typename SinglyLinkedList<T>::Node* head)
    {
        using Node = typename SinglyLinkedList<T>::Node;

        if (!head || !head->next)
            return head;

        Node* sorted = nullptr;

        Node* current = head;

        while (current != nullptr){
            Node* next = current->next;
            current->next = nullptr;

            if (sorted == nullptr || current->data <= sorted->data){
                current->next = sorted;
                sorted = current;
            }else {
                Node* temp = sorted;

                while (temp->next && (temp->next->data) < current->data){
                    temp = temp->next;
                }

                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }

        return sorted;
    }

    template<class T>
    void insertionSort(SinglyLinkedList<T>& list){
        using Node = typename SinglyLinkedList<T>::Node;

        Node* newHead = insertionSort<T>(list.getHead());

        list.setHead(newHead);
    }

    //Rekurencja do sortowania szybkiego
    //dzieli listę na 3 części(mniejsze, równe i większe od piwota)
    // wstawia wartości w odpowiednie miejsce
    template<class T>
    typename SinglyLinkedList<T>::Node* quickSortRecursive(typename SinglyLinkedList<T>::Node* head, int currentSize,Parameters::Pivots pivotType) {
        using Node = typename SinglyLinkedList<T>::Node;

        if (!head || !head->next) return head;

        Node* pivotNode = head;
        switch (pivotType) {

            case Parameters::Pivots::middle:
                for (int i = 0; i < currentSize / 2; i++)
                    pivotNode = pivotNode->next;
            break;

            case Parameters::Pivots::random: {
                int r = rand() % currentSize;
                for (int i = 0; i < r; i++)
                    pivotNode = pivotNode->next;
                break;
            }

            case Parameters::Pivots::left:
                pivotNode = head;
            break;

            case Parameters::Pivots::right:
                while (pivotNode->next)
                    pivotNode = pivotNode->next;
            break;

            default:
                pivotNode = head;
        }

        T pivotValue = pivotNode->data;


        Node *lessHead = nullptr, *equalHead = nullptr, *greaterHead = nullptr;
        int lessSize = 0, greaterSize = 0;

        Node* current = head;
        while (current) {
            Node* next = current->next;
            current->next = nullptr;

            if ((current->data) < pivotValue) {
                current->next = lessHead;
                lessHead = current;
                lessSize++;
            } else if (current->data > pivotValue) {
                current->next = greaterHead;
                greaterHead = current;
                greaterSize++;
            } else {
                current->next = equalHead;
                equalHead = current;
            }
            current = next;
        }

        lessHead = quickSortRecursive<T>(lessHead, lessSize, pivotType);
        greaterHead = quickSortRecursive<T>(greaterHead, greaterSize, pivotType);


        Node* newHead = nullptr;
        Node* tail = nullptr;


        auto append = [&](Node* section) {
            if (!section) return;
            if (!newHead) {
                newHead = section;
            } else {
                tail->next = section;
            }
            tail = section;
            while (tail->next) tail = tail->next;
        };

        append(lessHead);
        append(equalHead);
        append(greaterHead);

        return newHead;
    }


    //Sortowanie szybkie
    //wywoła metodę rekurencyjną i ustawia nową głowę
    template<class T>
    void quickSort(SinglyLinkedList<T>& list, Parameters::Pivots pivotType) {
        if (list.getSize() <= 1) return;

        list.head = quickSortRecursive<T>(list.head, list.size, pivotType);
    }



    // Ogólny szablon dla liczb
    template<typename T>
    double getNormalizedValue(T value, T min, T max) {
        if (max == min) return 0.0;
        return static_cast<double>(value - min) / static_cast<double>(max - min);
    }



    // Obsługiwanie stringów
    // Oblicza przybliżoną pozycję elementu na podstawie wartości ASCII pierwszego znaku
    template<>
    inline double getNormalizedValue<std::string>(std::string value, std::string min, std::string max) {
        if (max == min) return 0.0;


        unsigned char v = value.empty() ? 0 : value[0];
        unsigned char mi = min.empty() ? 0 : min[0];
        unsigned char ma = max.empty() ? 0 : max[0];

        if (ma == mi) return 0.0;
        return static_cast<double>(v - mi) / static_cast<double>(ma - mi);
    }


    //Sortowanie kubełkowe
    //Tworzy kubełki w których przechowywane są wartości
    //Robi alokacje pamięci dla kubełków
    //Na podstawie wzoru rozdziela wartości do odpowiednich kubełków
    //Sortuje elementy wewnątrz kubełków
    //scala kubełki
    template<class T>
    void bucketSort(SinglyLinkedList<T>& singlyList) {
        const int size = singlyList.getSize();
        const int bucketCount = std::max(1, static_cast<int>(sqrt(size)));
        T max = singlyList.findMax();
        T min = singlyList.findMin();

        if (max == min) return;

        auto* buckets= new SinglyLinkedList<T>[bucketCount];

        typename SinglyLinkedList<T>::Node* current  = singlyList.getHead();
        while (current != nullptr) {
            double norm = getNormalizedValue(current->data, min, max);
            int bucketIndex = static_cast<int>(norm * (bucketCount - 1));

            if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;

            buckets[bucketIndex].push(current->data);
            current = current->next;
        }

        singlyList = SinglyLinkedList<T>();
        for (int i = 0; i < bucketCount; i++) {
            if (buckets[i].getSize() > 0) {
                insertionSort(buckets[i]);
            }
            typename SinglyLinkedList<T>::Node* bucketNode= buckets[i].getHead();
            while (bucketNode != nullptr) {
                singlyList.push(bucketNode->data);
                bucketNode = bucketNode->next;
            }
        }
        delete[] buckets;
    }


    //Sortowanie Shell
    // Wykonuje porównania elementów oddalonych o zmniejszający się gap.
    template<class T>
    void shellSort(SinglyLinkedList<T>& list, Parameters::ShellParameters shellParameter) {
        using Node = typename SinglyLinkedList<T>::Node;

        const int size = list.getSize();
        Node* head = list.getHead();

        if (shellParameter == Parameters::ShellParameters::option1){
            for (int gap = size / 2; gap > 0; gap /= 2) {
                for (int i = gap; i < size; i++) {

                    Node* iNode = head;
                    for (int j = 0; j < i; j++) iNode = iNode->next;
                    T temp = iNode->data;

                    int j = i;

                    while (j >= gap) {

                        Node* jGapNode = head;
                        for (int k = 0; k < j - gap; k++)
                            jGapNode = jGapNode->next;

                        if (jGapNode->data <= temp)
                            break;

                        Node* jNode = jGapNode;
                        for (int k = 0; k < gap; k++)
                            jNode = jNode->next;

                        jNode->data = jGapNode->data;

                        j -= gap;
                    }

                    Node* insertNode = head;
                    for (int k = 0; k < j; k++)
                        insertNode = insertNode->next;

                    insertNode->data = temp;
                }
            }

        }else if (shellParameter == Parameters::ShellParameters::option2) {
            int gap = 1;

            while (gap < size / 3)
                gap = 3 * gap + 1;

            while (gap > 0) {

                for (int i = gap; i < size; i++) {

                    Node* iNode = head;
                    for (int j = 0; j < i; j++)
                        iNode = iNode->next;

                    T temp = iNode->data;

                    int j = i;

                    while (j >= gap) {

                        Node* jGapNode = head;
                        for (int k = 0; k < j - gap; k++)
                            jGapNode = jGapNode->next;

                        if (jGapNode->data <= temp)
                            break;

                        Node* jNode = jGapNode;
                        for (int k = 0; k < gap; k++)
                            jNode = jNode->next;

                        jNode->data = jGapNode->data;

                        j -= gap;
                    }

                    Node* insertNode = head;
                    for (int k = 0; k < j; k++)
                        insertNode = insertNode->next;

                    insertNode->data = temp;
                }

                gap /= 3;
            }
        }
    }
}

#endif //SINGLYLISTSORT_H
