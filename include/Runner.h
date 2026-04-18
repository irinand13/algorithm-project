
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
            case Parameters::Structures::stack: {
                Stack<T> stack = FileReader::readToStack<T>(inFile);
                quickSortStack(stack);
                if(stack.isSorted()) std::cout<<"Stack is sorted!"<<std::endl;
                else std::cout<<"Stack is not sorted!"<<std::endl;
                FileWriter::writeStructureToFile<T>(Parameters::outputFile, stack);
                break;
            }
            case Parameters::Structures::binaryTree: {
                Array<T> rawData = FileReader::readToArray<T>(inFile);
                BinaryTree<T> tree;

                for(int i = 0; i < rawData.getSize(); i++) {
                    tree.add(rawData[i]);
                }

                if(tree.isSorted()) std::cout<<"Binary tree is sorted!"<<std::endl;
                else std::cout<<"Binary tree is not sorted!"<<std::endl;
                FileWriter::writeStructureToFile<T>(Parameters::outputFile, tree);
                break;
            }

            default: std::cerr << "Unsupported structure!"<<std::endl;
        }
    }

    template <typename T>
    void runBenchmark() {
        FileWriter::prepareFile(Parameters::resultsFile);
        std::ofstream file(Parameters::resultsFile, std::ios::app);

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
            case Parameters::Structures::stack:runBenchmarkStack<T>(file, size, iterations); break;
            case Parameters::Structures::binaryTree: runBenchmarkBinaryTree<T>(file, size, iterations); break;
            default: std::cerr << "Error: Unsupported structure!"<<std::endl;
        }

        file.close();
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
    void runBenchmarkStack(std::ofstream& file, int size, int iterations) {
        if (iterations <= 0) return;
        if (size <= 0) return;

        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        Stack<T> stack = DataGenerator::generateStack<T>(size);
        for (int i = 0; i < iterations; i++) {
            Stack<T> copy = stack;
            auto start = std::chrono::high_resolution_clock::now();
            quickSortStack(copy);
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
    void runBenchmarkBinaryTree(std::ofstream& file, int size, int iterations) {
        if (iterations <= 0 || size <= 0) return;

        long long sum = 0;
        long long minTime = LLONG_MAX;
        long long maxTime = LLONG_MIN;

        Array<T> rawData = DataGenerator::generateArray<T>(size, Parameters::distribution);

        for (int i = 0; i < iterations; i++) {
            BinaryTree<T> tree;

            auto start = std::chrono::high_resolution_clock::now();

            // Budowa drzewa = Sortowanie
            for(int j = 0; j < size; j++) {
                tree.add(rawData[j]);
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            sum += duration;
            if(duration < minTime) minTime = duration;
            if(duration > maxTime) maxTime = duration;

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

    template <typename T>
    void quickSortStack(Stack<T>& stack) {

        if (stack.getSize() <= 1) return;

        T pivot = stack.top();
        stack.pop();

        Stack<T> less;
        Stack<T> equal;
        Stack<T> greater;

        equal.push(pivot);

        while (stack.getSize() > 0) {
            T current = stack.top();
            stack.pop();

            if (current < pivot) {
                less.push(current);
            } else if (current > pivot) {
                greater.push(current);
            } else {
                equal.push(current);
            }
        }

        quickSortStack(less);
        quickSortStack(greater);

        auto append = [&](Stack<T>& source) {
            Stack<T> temp;
            while (source.getSize() > 0) {
                temp.push(source.top());
                source.pop();
            }
            while (temp.getSize() > 0) {
                stack.push(temp.top());
                temp.pop();
            }
        };

        append(greater);
        append(equal);
        append(less);
    }

};
#endif //APPLICATION_H
