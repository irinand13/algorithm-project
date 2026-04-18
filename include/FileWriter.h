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
    inline void writeDataToFile(
        int size,
        int iterations,
        int duration) {

        std::ofstream file(Parameters::outputFile, std::ios::app);

        if (!file.is_open()) {
            std::cout<<"Can't open output file"<<std::endl;
            return;
        }

        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm* time = std::localtime(&nowTime);

        file << std::put_time(time, "%Y-%m-%d %H:%M:%S") <<",";
        file << std::to_string(static_cast<int>(Parameters::algorithm)) << ",";
        file << std::to_string(static_cast<int>(Parameters::structure)) << ",";
        file << size << ",";
        file << std::to_string(static_cast<int>(Parameters::dataType)) << ",";
        file << std::to_string(static_cast<int>(Parameters::distribution)) << ",";
        file << iterations << ",";
        file << std::to_string(static_cast<int>(Parameters::pivot)) << ",";
        file << std::to_string(static_cast<int>(Parameters::shellParameter)) << ",";

        file << duration << std::endl;
    }
    inline void writeResultToFile(long long average, long long min, long long max) {
        std::ofstream file(Parameters::outputFile, std::ios::app);

        if (!file.is_open()) {
            std::cout<<"Can't open output file"<<std::endl;
            return;
        }

        file << average << "," << min << "," << max << "\n";
    }
    
}
#endif //FILEWRITER_H
