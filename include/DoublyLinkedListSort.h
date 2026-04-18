//
// Created by iraan on 15.04.2026.
//
#include "DoublyLinkedList.h"
#ifndef DOUBLYLINKEDLISTSORT_H
#define DOUBLYLINKEDLISTSORT_H
namespace DoublyLinkedListSort {

    template<class T>
    typename DoublyLinkedList<T>::Node*
    insertionSort(typename DoublyLinkedList<T>::Node* head)
    {
        using Node = typename DoublyLinkedList<T>::Node;

        if (!head || !head->next)
            return head;

        Node* sorted = nullptr;
        Node* current = head;

        while (current != nullptr) {
            Node* next = current->next;

            current->prev = current->next = nullptr;

            if (!sorted || current->data <= sorted->data) {
                current->next = sorted;
                if (sorted) sorted->prev = current;
                sorted = current;
            } else {
                Node* temp = sorted;

                while (temp->next && (temp->next->data) < current->data)
                    temp = temp->next;

                current->next = temp->next;
                if (temp->next)
                    temp->next->prev = current;

                temp->next = current;
                current->prev = temp;
            }

            current = next;
        }

        return sorted;
    }

    template<class T>
    void insertionSort(DoublyLinkedList<T>& list) {
        list.head = insertionSort<T>(list.head);
    }


    template<class T>
    typename DoublyLinkedList<T>::Node*
    quickSortRecursive(typename DoublyLinkedList<T>::Node* head, int size,Parameters::Pivots pivotType)
    {
        using Node = typename DoublyLinkedList<T>::Node;

        if (!head || !head->next)
            return head;

        Node* pivotNode = head;

        switch (pivotType) {

            case Parameters::Pivots::middle:
                for (int i = 0; i < size / 2; i++)
                    pivotNode = pivotNode->next;
                break;

            case Parameters::Pivots::random: {
                int r = rand() % size;
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
            current->prev = current->next = nullptr;

            if ((current->data) < pivotValue) {
                current->next = lessHead;
                if (lessHead) lessHead->prev = current;
                lessHead = current;
                lessSize++;
            }
            else if (current->data > pivotValue) {
                current->next = greaterHead;
                if (greaterHead) greaterHead->prev = current;
                greaterHead = current;
                greaterSize++;
            }
            else {
                current->next = equalHead;
                if (equalHead) equalHead->prev = current;
                equalHead = current;
            }

            current = next;
        }

        lessHead = quickSortRecursive<T>(lessHead, lessSize,pivotType);
        greaterHead = quickSortRecursive<T>(greaterHead, greaterSize, pivotType);

        Node* newHead = nullptr;
        Node* tail = nullptr;

        auto append = [&](Node* section) {
            if (!section) return;

            if (!newHead) {
                newHead = section;
                tail = section;
            } else {
                tail->next = section;
                section->prev = tail;
            }

            while (tail->next)
                tail = tail->next;
        };

        append(lessHead);
        append(equalHead);
        append(greaterHead);

        return newHead;
    }

    template<class T>
    void quickSort(DoublyLinkedList<T>& list,Parameters::Pivots pivotType) {
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
    template<>
    inline double getNormalizedValue<std::string>(std::string value, std::string min, std::string max) {
        if (max == min) return 0.0;


        unsigned char v = value.empty() ? 0 : value[0];
        unsigned char mi = min.empty() ? 0 : min[0];
        unsigned char ma = max.empty() ? 0 : max[0];

        if (ma == mi) return 0.0;
        return static_cast<double>(v - mi) / static_cast<double>(ma - mi);
    }

    template<class T>
    void bucketSort(DoublyLinkedList<T>& list) {

        const int size = list.getSize();
        const int bucketCount = std::max(1, (int)sqrt(size));

        T max = list.findMax();
        T min = list.findMin();

        if (max == min) return;

        auto* buckets = new DoublyLinkedList<T>[bucketCount];

        using Node = typename DoublyLinkedList<T>::Node;

        Node* current = list.getHead();

        while (current) {
            double norm = getNormalizedValue(current->data, min, max);
            int index = static_cast<int>(norm * (bucketCount - 1));

            if (index < 0) index = 0;
            if (index >= bucketCount) index = bucketCount - 1;

            buckets[index].push_back(current->data);
            current = current->next;
        }

        list.clear();

        for (int i = 0; i < bucketCount; i++) {

            if (buckets[i].getSize() > 0)
                insertionSort(buckets[i]);

            Node* node = buckets[i].getHead();

            while (node) {
                list.push(node->data);
                node = node->next;
            }
        }

        delete[] buckets;
    }

    template<class T>
    void shellSort(DoublyLinkedList<T>& list, Parameters::ShellParameters shellParameter) {
        using Node = typename DoublyLinkedList<T>::Node;

        const int size = list.getSize();
        Node* head = list.getHead();

        auto getNode = [&](int index) -> Node* {
        Node* curr = head;

        for (int i = 0; i < index; i++) curr = curr->next;

        return curr;
        };

        if (shellParameter == Parameters::ShellParameters::option1) {


            for (int gap = size / 2; gap > 0; gap /= 2) {
                for (int i = gap; i < size; i++) {

                    Node* iNode = getNode(i);
                    T temp = iNode->data;

                    Node* jNode = iNode;

                    while (jNode != nullptr) {

                        Node* jGapNode = jNode;

                        for (int k = 0; k < gap && jGapNode; k++) jGapNode = jGapNode->prev;

                        if (!jGapNode || jGapNode->data <= temp) break;

                        jNode->data = jGapNode->data;
                        jNode = jGapNode;
                    }

                    if (jNode) jNode->data = temp;
                }
            }

        } else if (shellParameter == Parameters::ShellParameters::option2) {

            int gap = 1;
            while (gap < size / 3) gap = 3 * gap + 1;

            while (gap > 0) {

                for (int i = gap; i < size; i++) {

                    Node* iNode = getNode(i);
                    T temp = iNode->data;

                    Node* jNode = iNode;

                    while (jNode) {

                        Node* jGapNode = jNode;

                        for (int k = 0; k < gap && jGapNode; k++) jGapNode = jGapNode->prev;

                        if (!jGapNode || jGapNode->data <= temp) break;


                        jNode->data = jGapNode->data;
                        jNode = jGapNode;
                    }

                    if (jNode) jNode->data = temp;
                }

                gap /= 3;
            }
        }
    }

}
#endif //DOUBLYLINKEDLISTSORT_H
