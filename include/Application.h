
//
// Created by iraan on 15.04.2026.
//
#pragma once

#include "Parameters.h"
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "ArraySort.h"
#include "SinglyLinkedListSort.h"
#include "DoublyLinkedListSort.h"
#include "FileReader.h"

#ifndef APPLICATION_H
#define APPLICATION_H
class Application {
    public:
    void run() {

        if (Parameters::runMode == Parameters::RunModes::help) {
            Parameters::help();
            return;
        }

        switch (Parameters::dataType) {
            case Parameters::DataTypes::typeInt: startWithTemplate<int>(); break;
            case Parameters::DataTypes::typeDouble: startWithTemplate<double>(); break;
            case Parameters::DataTypes::typeString: startWithTemplate<std::string>(); break;
            case Parameters::DataTypes::typeFloat: startWithTemplate<float>(); break;
            case Parameters::DataTypes::typeChar: startWithTemplate<char>(); break;
            case Parameters::DataTypes::tyleUnsignedInt: startWithTemplate<unsigned>(); break;
            default: std::cerr << "Error: Unsupported data type!"<<std::endl;
        }

    }
private:
    template <typename T>
    void startWithTemplate() {
        if (Parameters::runMode == Parameters::RunModes::benchmark) {
            runBenchmark<T>();
        }else if (Parameters::runMode == Parameters::RunModes::singleFile) {
            runSingleFile<T>();
        }

    }

    template <typename T>
    void runSingleFile() {
        std::string inFile = Parameters::inputFile;
        std::string outFile = Parameters::outputFile;

        switch (Parameters::structure) {
            case Parameters::Structures::array: {
                Array<T> array = FileReader::readToArray<T>(inFile);
                sortArray(array);

                if(array.isSorted()) std::cout<<"Array is sorted!"<<std::endl;
                else std::cout<<"Array is not sorted!"<<std::endl;
                break;
            }
            case Parameters::Structures::singleList: {
                SinglyLinkedList<T> singlyList = FileReader::readToSinglyLinkedList<T>(inFile);
                sortSinglyLinkedList(singlyList);

                if(singlyList.isSorted()) std::cout<<"Singly list is sorted!"<<std::endl;
                else std::cout<<"Singly list is not sorted!"<<std::endl;
                break;
            }
            case Parameters::Structures::doubleList: {
                DoublyLinkedList<T> doublyList = FileReader::readToDoublyLinkedList<T>(inFile);
                sortDoublyLinkedList(doublyList);

                if(doublyList.isSorted()) std::cout<<"Doubly list is sorted!"<<std::endl;
                else std::cout<<"Doubly  list is not sorted!"<<std::endl;
                break;
            }
            default: std::cerr << "Unsupported structure!"<<std::endl;
        }
    }

    template <typename T>
    void runBenchmark() {
        int size = Parameters::structureSize;
        int iterations = Parameters::iterations;

        switch (Parameters::structure) {
            case Parameters::Structures::array: runBenchmarkArray<T>(size, iterations); break;
            default: ;
        }
    }

    template <typename T>
    void runBenchmarkArray(int size, int iterations) {
        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = 0;

        for (int i = 0; i < iterations; i++) {
        }

    }

    template <typename T>
    void sortArray(Array<T>& array) {
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::bucket:ArraySort::bucketSort(array); break;
            case Parameters::Algorithms::shell: ArraySort::shellSort(array,Parameters::shellParameter); break;
            case Parameters::Algorithms::quick:ArraySort::quickSort(array,Parameters::pivot);break;
            default: std::cerr << "Unsupported algorithm!"<<std::endl;
        }
    }

    template <typename T>
    void sortSinglyLinkedList(SinglyLinkedList<T>& list) {
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::bucket:SinglyLinkedListSort::bucketSort(list); break;
            case Parameters::Algorithms::shell: SinglyLinkedListSort::shellSort(list,Parameters::shellParameter); break;
            case Parameters::Algorithms::quick: SinglyLinkedListSort::quickSort(list,Parameters::pivot);break;
            default: std::cerr << "Unsupported algorithm!"<<std::endl;
        }
    }

    template <typename T>
    void sortDoublyLinkedList(DoublyLinkedList<T>& list) {
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::bucket:DoublyLinkedListSort::bucketSort(list); break;
            case Parameters::Algorithms::shell: DoublyLinkedListSort::shellSort(list,Parameters::shellParameter); break;
            case Parameters::Algorithms::quick: DoublyLinkedListSort::quickSort(list,Parameters::pivot);break;
            default: std::cerr << "Unsupported algorithm!"<<std::endl;
        }
    }
};
#endif //APPLICATION_H
