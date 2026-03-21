//
// Created by iraan on 20.03.2026.
//

#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

// Dynamiczna tablica, która jest inicjalizowana jako szablon
template<class T>
class Array {
private:
    int array_size;
    T *data;

public:

    explicit Array(int size) {
        if (size > 0) {
            data = new T[size]{};
            array_size = size;
        } else {
            array_size = 0;
            throw std::invalid_argument("Array size must be greater than 0");
        }
    }

    ~Array() {
        delete[] data;
    }

    void add(int index, const T& value) {
        if (index >= array_size || index < 0) {
            throw std::invalid_argument("Index out of range");
        }else{
            data[index] = value;
        }
    }
};



#endif //ARRAY_H
