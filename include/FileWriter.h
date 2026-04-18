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

    inline void prepareFile(const std::string& filename) {
        std::ifstream check(filename);
        bool isEmpty = check.peek() == std::ifstream::traits_type::eof();
        check.close();

        if (isEmpty) {
            std::ofstream file(filename);
            file << "timestamp,algorithm,structure,size,dataType,distribution,iterations,pivot,shellParam,type,duration_us\n";
        }
    }

    inline void writeSingleIterationToFile(std::ofstream& file,
        int size,
        int iterations,
        long long duration) {

        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm* timePtr = std::localtime(&nowTime);

        file << std::put_time(timePtr, "%Y-%m-%d %H:%M:%S") << ","
             << std::to_string(static_cast<int>(Parameters::algorithm)) << ","
             << std::to_string(static_cast<int>(Parameters::structure)) << ","
             << size << ","
             << std::to_string(static_cast<int>(Parameters::dataType)) << ","
             << std::to_string(static_cast<int>(Parameters::distribution)) << ","
             << iterations << ","
             << std::to_string(static_cast<int>(Parameters::pivot)) << ","
             << std::to_string(static_cast<int>(Parameters::shellParameter)) << ","
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
}
#endif //FILEWRITER_H
