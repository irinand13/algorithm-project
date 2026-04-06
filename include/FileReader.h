//
// Created by iraan on 23.03.2026.
//
#pragma once

#include <fstream>
#include <Array.h>
#include <SinglyLinkedList.h>
#include <DoublyLinkedList.h>
using namespace std;

#ifndef FILEREADER_H
#define FILEREADER_H

//Odczytuje wartości z pliku, tworzy tablicę oraz dodaje
//do niej odczytane wartości
template <typename T>
Array <T> readToArray (const string& fileName) {
    fstream file(fileName);
    int size;
    T t;

    if(!file.is_open()) {
        cerr << "Error opening file " << fileName << endl;
        return Array<T>(0);
    }else {
        file>>size;

        Array <T> array(size);
        for (int i = 0; i < size; i++) {
            file>>t;
            array.set(i,t);
        }
        return array;
    }
}

//Odczytuje wartości z pliku, tworzy listę jednokierunkową oraz dodaje
//do niej odczytane wartości
template <typename T>
SinglyLinkedList<T> readToSinlyLinkedList (const string& fileName) {
    fstream file(fileName);
    int size;
    T t;

    if(!file.is_open()) {
        cerr << "Error opening file " << fileName << endl;
        return SinglyLinkedList<T>(0);
    }else {
        file>>size;
        SinglyLinkedList<T> list{};
        for (int i = 0; i < size; i++) {
            file>>t;
            list.push(t);
        }
        return list;
    }
}

//Odczytuje wartości z pliku, tworzy listę dwukierunkową oraz dodaje
//do niej odczytane wartości
template <typename T>
DoublyLinkedList<T> readToDoublyLinkedList (const string& fileName) {
    fstream file(fileName);
    int size;
    T t;

    if(!file.is_open()) {
        cerr << "Error opening file " << fileName << endl;
        return DoublyLinkedList<T>(0);
    }else {
        file>>size;
        DoublyLinkedList<T> list{};
        for (int i = 0; i < size; i++) {
            file>>t;
            list.push(t);
        }
        return list;
    }
}

#endif //FILEREADER_H
