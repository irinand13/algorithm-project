//
// Created by iraan on 23.03.2026.
//
#pragma once

#include <fstream>
#include <Array.h>
#include <SinglyLinkedList.h>
#include <DoublyLinkedList.h>

#include "BinaryTree.h"
#include "Stack.h"
using namespace std;

#ifndef FILEREADER_H
#define FILEREADER_H
class FileReader {
    public:
    //Odczytuje wartości z pliku, tworzy tablicę oraz dodaje
    //do niej odczytane wartości
    template <typename T>
    static Array <T> readToArray (const string& fileName) {
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
    static SinglyLinkedList<T> readToSinglyLinkedList (const string& fileName) {
        fstream file(fileName);
        int size;
        T t;

        if(!file.is_open()) {
            cerr << "Error opening file " << fileName << endl;
            return SinglyLinkedList<T>();
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
    static DoublyLinkedList<T> readToDoublyLinkedList (const string& fileName) {
        fstream file(fileName);
        int size;
        T t;

        if(!file.is_open()) {
            cerr << "Error opening file " << fileName << endl;
            return DoublyLinkedList<T>();
        }else {
            file>>size;
            DoublyLinkedList<T> list{};
            for (int i = 0; i < size; i++) {
                file>>t;
                list.push_back(t);
            }
            return list;
        }
    }

    // Odczytuje wartości z pliku i dodaje je na stos
    template <typename T>
    static Stack<T> readToStack(const string& fileName) {
        fstream file(fileName);
        int size;
        T t;

        if(!file.is_open()) {
            cerr << "Error opening file " << fileName << endl;
            return Stack<T>();
        } else {
            file >> size;
            Stack<T> stack{};
            for (int i = 0; i < size; i++) {
                file >> t;
                stack.push(t);
            }
            return stack;
        }
    }

    // Odczytuje wartości z pliku i buduje drzewo binarne (BST)
    template <typename T>
    static BinaryTree<T> readToBinaryTree(const string& fileName) {
        fstream file(fileName);
        int size;
        T t;

        if(!file.is_open()) {
            cerr << "Error opening file " << fileName << endl;
            return BinaryTree<T>();
        } else {
            file >> size;
            BinaryTree<T> tree{};
            for (int i = 0; i < size; i++) {
                file >> t;
                tree.add(t);
            }
            return tree;
        }
    }
};
#endif //FILEREADER_H
