
//
// Created by iraan on 15.04.2026.
//
#pragma once

#include "Parameters.h"
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "ArraySort.h"
#include "DataGenerator.h"
#include "SinglyLinkedListSort.h"
#include "DoublyLinkedListSort.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <chrono>
#include <climits>

#ifndef APPLICATION_H
#define APPLICATION_H
class Runner {
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
            case Parameters::DataTypes::typeUnsignedInt: startWithTemplate<unsigned>(); break;
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
        std::cout << "DEBUG: Start runSingleFile" << std::endl;
        std::string inFile = Parameters::inputFile;
        std::string outFile = Parameters::outputFile;

        switch (Parameters::structure) {
            case Parameters::Structures::array: {
                Array<T> array = FileReader::readToArray<T>(inFile);
                sortArray(array);

                if(array.isSorted()) std::cout<<"Array is sorted!"<<std::endl;
                else std::cout<<"Array is not sorted!"<<std::endl;
                FileWriter::writeStructureToFile<T>(Parameters::outputFile, array);
                break;
            }
            case Parameters::Structures::singleList: {
                SinglyLinkedList<T> singlyList = FileReader::readToSinglyLinkedList<T>(inFile);
                sortSinglyLinkedList(singlyList);

                if(singlyList.isSorted()) std::cout<<"Singly list is sorted!"<<std::endl;
                else std::cout<<"Singly list is not sorted!"<<std::endl;
                FileWriter::writeStructureToFile<T>(Parameters::outputFile, singlyList);
                break;
            }
            case Parameters::Structures::doubleList: {
                DoublyLinkedList<T> doublyList = FileReader::readToDoublyLinkedList<T>(inFile);
                sortDoublyLinkedList(doublyList);

                if(doublyList.isSorted()) std::cout<<"Doubly list is sorted!"<<std::endl;
                else std::cout<<"Doubly  list is not sorted!"<<std::endl;
                FileWriter::writeStructureToFile<T>(Parameters::outputFile, doublyList);
                break;
            }
            default: std::cerr << "Unsupported structure!"<<std::endl;
        }
    }

    template <typename T>
    void runBenchmark() {
        FileWriter::prepareFile(Parameters::outputFile);
        std::ofstream file(Parameters::outputFile, std::ios::app);

        if (!file.is_open()) {
            std::cerr << "Can't open file\n";
            return;
        }

        int size = Parameters::structureSize;
        int iterations = Parameters::iterations;

        switch (Parameters::structure) {
            case Parameters::Structures::array: runBenchmarkArray<T>(file, size, iterations); break;
            case Parameters::Structures::singleList: runBenchmarkSinglyLinkedList<T>(file, size, iterations); break;
            case Parameters::Structures::doubleList: runBenchmarkDoublyLinkedList<T>(file, size, iterations); break;
            default: std::cerr << "Error: Unsupported structure!"<<std::endl;
        }
    }

    template <typename T>
    void runBenchmarkArray(std::ofstream& file, int size, int iterations) {
        if (iterations <= 0) return;
        if (size <= 0) return;

        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        Array<T> array = DataGenerator::generateArray<T>(size,Parameters::distribution);
        for (int i = 0; i < iterations; i++) {
            Array<T> copy = array;

            auto start = std::chrono::high_resolution_clock::now();

            sortArray(copy);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;

            if(duration < minTime)minTime = duration;
            if(duration > maxTime)maxTime = duration;
            FileWriter::writeSingleIterationToFile(file, size, iterations, duration);
        }
        long long average = sum / iterations;
        FileWriter::writeSummary(file, average, minTime, maxTime);
    }

    template <typename T>
    void runBenchmarkSinglyLinkedList(std::ofstream& file, int size, int iterations) {
        if (iterations <= 0) return;
        if (size <= 0) return;

        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        SinglyLinkedList<T> singlyList = DataGenerator::generateSinglyLinkedList<T>(size, Parameters::distribution);

        for (int i = 0; i < iterations; i++) {
            SinglyLinkedList<T> copy = singlyList;

            auto start = std::chrono::high_resolution_clock::now();

            sortSinglyLinkedList(copy);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;

            if(duration < minTime)minTime = duration;
            if(duration > maxTime)maxTime = duration;

            FileWriter::writeSingleIterationToFile(file, size, iterations, duration);
        }
        long long average = sum / iterations;
        FileWriter::writeSummary(file, average, minTime, maxTime);

    }

    template <typename T>
    void runBenchmarkDoublyLinkedList(std::ofstream& file,int size, int iterations) {
        if (iterations <= 0) return;
        if (size <= 0) return;

        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        DoublyLinkedList<T> doublyList = DataGenerator::generateDoublyLinkedList<T>(size, Parameters::distribution);
        for (int i = 0; i < iterations; i++) {
            DoublyLinkedList<T> copy = doublyList;

            auto start = std::chrono::high_resolution_clock::now();

            sortDoublyLinkedList(copy);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;

            if(duration < minTime)minTime = duration;
            if(duration > maxTime)maxTime = duration;

            FileWriter::writeSingleIterationToFile(file, size, iterations, duration);
        }
        long long average = sum / iterations;
        FileWriter::writeSummary(file, average, minTime, maxTime);
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
