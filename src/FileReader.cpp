#include <fstream>
#include <string>

#include "Array.h"
#include "SinglyLinkedList.h"
//
// Created by iraan on 22.03.2026.
//
using namespace std;
#include "FileReader.h"
#include <Types.h>

void readFile(string& fileName, StructureType type,DataType dataType) {
    fstream plik(fileName, std::ios::in);
    string line;
    int size;

    if (type == StructureType::Array) {
        getline(plik, line);
        size = atoi(line.c_str());

        if (dataType == DataType::Int) {
            Array<int>* arrayi = new Array<int>(size);
            for (int i = 2; i <= size; i++) {
                getline(plik, line);
                int value = atoi(line.c_str());
                arrayi->add(i, value);
            }

        }else if (dataType == DataType::Float) {
            Array<float>* arrayf = new Array<float>(size);

            for (int i = 2; i <= size; i++) {
                getline(plik, line);
                float value = atof(line.c_str());
                arrayf->add(i, value);
            }
        }


    }
}