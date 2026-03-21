//
// Created by iraan on 20.03.2026.
//

#ifndef ARRAY_H
#define ARRAY_H

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
        }
    }

    ~Array() {
        delete[] data;
    }
};



#endif //ARRAY_H
