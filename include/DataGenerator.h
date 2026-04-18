//
// Created by iraan on 16.04.2026.
//
#pragma once
#include <random>
#include "Parameters.h"
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "ArraySort.h"
#include "SinglyLinkedListSort.h"
#include "DoublyLinkedListSort.h"

namespace DataGenerator
{
    template <typename T>
    T generateValue();

    template <>
    inline int generateValue<int>(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int>

        dist(INT_MIN, INT_MAX);

        return dist(gen);
    }

    template <>
    inline float generateValue<float>(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float>

        dist(-1000.0f, 1000.0f);

        return dist(gen);
    }

    template <>
    inline double generateValue<double>(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double>
        dist(-1000.0, 1000.0);

        return dist(gen);
    }

    template <>
    inline char generateValue<char>(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int>
        dist(32, 126);

        return static_cast<char>(dist(gen));
    }

    template <>
    inline std::string generateValue<std::string>(){
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> lenDist(3, 10);
        static std::uniform_int_distribution<int> charDist(97, 122);

        const int len = lenDist(gen);

        std::string s;
        for (int i = 0; i < len; i++)
            s.push_back(charDist(gen));

        return s;
    }

    template <typename T>
    void reverseArray(Array<T>& arr){
        int left = 0;
        int right = arr.size() - 1;

        while (left < right){
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    template <typename T>
    void reverseSinlyList(SinglyLinkedList<T>& list) {
        typename SinglyLinkedList<T>::Node* prev = nullptr;
        typename SinglyLinkedList<T>::Node* current = list.getHead();
        typename SinglyLinkedList<T>::Node* next = nullptr;

        while (current != nullptr){
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        list.setHead(prev);
    }

    template <typename T>
    void reverseDoublyList(DoublyLinkedList<T>& list){
        typename DoublyLinkedList<T>::Node* current = list.getHead();
        typename DoublyLinkedList<T>::Node* temp = nullptr;

        while (current != nullptr){
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;

            current = current->prev;
        }

        if (temp != nullptr) list.setHead(temp->prev);
    }

    template <typename T>
    Array<T> generateArray(int size,Parameters::Distribution distribution){
        Array<T> arr(size);

        for (int i = 0; i < size; i++) arr[i] = generateValue<T>();


        switch (distribution) {
            case Parameters::Distribution::random:break;

            case Parameters::Distribution::ascending: {
                ArraySort::quickSort(arr);
                break;
            }

            case Parameters::Distribution::descending: {
                ArraySort::quickSort(arr);
                reverseArray(arr);
                break;
            }

            case Parameters::Distribution::ascending50Per: {
                int n = size;
                int half = n / 2;
                Array<T> tmp = arr;

                ArraySort::quickSort(tmp);
                for (int i = 0; i < half; i++)arr[i] = tmp[i];

                break;
            }

            default:
                break;
        }
        return arr;
    }

    template <typename T>
    SinglyLinkedList<T> generateSinglyLinkedList(int size, Parameters::Distribution distribution){
        SinglyLinkedList<T> list;

        for (int i = 0; i < size; i++)list.push(generateValue<T>());

        switch (distribution){
            case Parameters::Distribution::random:
                break;

            case Parameters::Distribution::ascending: {
                SinglyLinkedListSort::quickSort(list);
                break;
            }

            case Parameters::Distribution::descending: {
                SinglyLinkedListSort::quickSort(list);
                reverseSinglyList(list);
                break;
            }

            case Parameters::Distribution::ascending50Per:{
                int n = list.getSize();
                int half = n / 2;

                SinglyLinkedList<T> first;
                SinglyLinkedList<T> second;

                auto* node = list.getHead();

                int i = 0;
                while (node != nullptr){
                    if (i < half)
                        first.push(node->data);
                    else
                        second.push(node->data);

                    node = node->next;
                    i++;
                }

                SinglyLinkedListSort::quickSort(first);

                list = first;

                auto* n2 = second.getHead();
                while (n2 != nullptr){
                    list.push(n2->data);
                    n2 = n2->next;
                }

                break;
            }

            default:
                break;
        }

        return list;
    }

    template <typename T>
    DoublyLinkedList<T> generateDoublyLinkedList(int size, Parameters::Distribution distribution){
    DoublyLinkedList<T> list;

    for (int i = 0; i < size; i++)
        list.push(generateValue<T>());

    switch (distribution){
        case Parameters::Distribution::random:
            break;

        case Parameters::Distribution::ascending:
            DoublyLinkedListSort::quickSort(list);
            break;

        case Parameters::Distribution::descending: {
            DoublyLinkedListSort::quickSort(list);
            reverseDoublyList(list);
            break;
        }

        case Parameters::Distribution::ascending50Per:{
            int n = list.getSize();
            int half = n / 2;

            DoublyLinkedList<T> first;
            DoublyLinkedList<T> second;

            auto* node = list.getHead();
            int i = 0;

            while (node != nullptr){
                if (i < half)first.push(node->data);
                else second.push(node->data);

                node = node->next;
                i++;
            }

            DoublyLinkedListSort::quickSort(first);

            list = first;

            auto* n2 = second.getHead();
            while (n2 != nullptr){
                list.push(n2->data);
                n2 = n2->next;
            }

            break;
        }

        default:
            break;
    }

    return list;
}

}
#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#endif //DATAGENERATOR_H
