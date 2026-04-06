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

    Array(const Array& other) {
        array_size = other.array_size;
        data = new T[array_size];

        for (int i = 0; i < array_size; i++) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        delete[] data;

        array_size = other.array_size;
        data = new T[array_size];

        for (int i = 0; i < array_size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    ~Array() {
        delete[] data;
    }

    void set(int index, const T& value) {
        if (index >= array_size || index < 0) {
            throw std::invalid_argument("Index out of range");
        }else{
            data[index] = value;
        }
    }

    void read() {
        std::cout<<"Array reading..."<<std::endl;
        for (int i = 0; i < array_size; i++) {
            std::cout<<data[i]<<std::endl;
        }
    }

};



#endif //ARRAY_H
