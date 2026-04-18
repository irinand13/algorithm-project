//
// Created by iraan on 18.04.2026.
//
#pragma once
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "Parameters.h"

#ifndef FILEWRITER_H
#define FILEWRITER_H
namespace FileWriter {
    inline bool headerWritten = false;

    inline std::string getAlgorithmName(Parameters::Algorithms alg) {
        switch(alg) {
            case Parameters::Algorithms::quick: return "QuickSort";
            case Parameters::Algorithms::shell: return "ShellSort";
            case Parameters::Algorithms::bucket: return "BucketSort";
            default: return "Unknown";
        }
    }

    inline std::string getStructureName(Parameters::Structures str) {
        switch(str) {
            case Parameters::Structures::stack: return "Stack";
            case Parameters::Structures::binaryTree: return "BinaryTree";
            case Parameters::Structures::array: return "Array";
            case Parameters::Structures::singleList: return "SinglyList";
            case Parameters::Structures::doubleList: return "DoubleList";
            default: return "Unknown";
        }
    }

    inline std::string getDataTypeName(Parameters::DataTypes dataType) {
        switch (dataType) {
            case Parameters::DataTypes::typeInt: return "int";
            case Parameters::DataTypes::typeFloat: return "float";
            case Parameters::DataTypes::typeDouble: return "double";
            case Parameters::DataTypes::typeString: return "string";
            case Parameters::DataTypes::typeChar: return "char";
            case Parameters::DataTypes::typeUnsignedInt: return "unsignedInt";

            default: return "Unknown";
        }
    }

    inline std::string getDistributionName(Parameters::Distribution dis) {
        switch (dis) {
            case Parameters::Distribution::random: return "Random";
            case Parameters::Distribution::ascending: return "Ascending";
            case Parameters::Distribution::descending: return "Descending";
            case Parameters::Distribution::ascending50Per: return "Ascending50Per";
            default: return "Unknown";
        }
    }

    inline std::string getPivotName(Parameters::Pivots pivot) {
        switch (pivot) {
            case Parameters::Pivots::random: return "Random";
            case Parameters::Pivots::middle: return "Middle";
            case Parameters::Pivots::left: return "Left";
            case Parameters::Pivots::right: return "Right";
            default: return "Unknown";
        }
    }

    inline std::string getShellParameterName(Parameters::ShellParameters shellParameter) {
        switch (shellParameter) {
            case Parameters::ShellParameters::option1: return "original";
            case Parameters::ShellParameters::option2: return "Knutha";
            default: return "Unknown";
        }
    }

    inline void prepareFile(const std::string& filename) {
        std::ifstream check(filename);
        bool fileExists = check.good();

        bool isEmpty = true;
        if (fileExists) {
            isEmpty = (check.peek() == std::ifstream::traits_type::eof());
        }
        check.close();

        if (!fileExists || isEmpty) {
            std::ofstream file(filename, std::ios::out);
            file << "timestamp;algorithm;structure;size;dataType;distribution;iterations;pivot;shellParam;type;duration_us\n";
            file.close();
        }
    }

    inline void writeSingleIterationToFile(std::ofstream& file,
        int size,
        int iterations,
        long long duration) {

        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm* timePtr = std::localtime(&nowTime);

        file << std::put_time(timePtr, "%Y-%m-%d %H:%M:%S") << ";"
             << getAlgorithmName(Parameters::algorithm) << ";"
             << getStructureName(Parameters::structure) << ";"
             << size << ";"
             << getDataTypeName(Parameters::dataType) << ";"
             << getDistributionName(Parameters::distribution) << ";"
             << iterations << ";"
             << getPivotName(Parameters::pivot) << ";"
             << getShellParameterName(Parameters::shellParameter) << ";"
             << "SINGLE," << duration << "\n";
    }


    inline void writeSummary(std::ofstream& file, long long avg, long long min, long long max) {
        file << ",,,,,,,,,AVG," << avg << "\n";
        file << ",,,,,,,,,MIN," << min << "\n";
        file << ",,,,,,,,,MAX," << max << "\n";
    }

    template <typename T, typename Container>
    static void writeStructureToFile(const std::string& filename, Container& container) {
        std::ofstream file(filename);
        if (!file.is_open()) return;

        file << container.getSize() << "\n";
        for (int i = 0; i < container.getSize(); ++i) {
            file << container[i] << "\n";
        }
    }

    template <typename T>
    static void writeInOrder(std::ofstream& file, typename BinaryTree<T>::Node* node) {
        if (node == nullptr) return;
        writeInOrder<T>(file, node->left);
        file << node->data << "\n";
        writeInOrder<T>(file, node->right);
    }

    template <typename T>
    static void writeStructureToFile(const std::string& filename, BinaryTree<T>& tree) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        file << tree.getSize() << "\n";
        writeInOrder<T>(file, tree.getRoot());
    }


}
#endif //FILEWRITER_H
