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
   Array<T> generateArray(int size)
    {
        Array<T> arr(size);

        for (int i = 0; i < size; i++)
            arr[i] = generateValue<T>();

        return arr;
    }

    template <typename T>
    SinglyLinkedList<T> generateSinglyLinkedList(int size){
        SinglyLinkedList<T> list;

        for (int i = 0; i < size; i++) list.push(generateValue<T>());

        return list;
    }
    template <typename T>
    DoublyLinkedList<T> generateDoublyLinkedList(int size) {
        DoublyLinkedList<T> list;
        for (int i = 0; i < size; i++) list.push_back(generateValue<T>());
        return list;
    }
}
#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#endif //DATAGENERATOR_H
