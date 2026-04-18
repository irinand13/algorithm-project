#include<iostream>

#include "ArraySort.h"
#include "FileReader.h"
#include "DataGenerator.h"
#include "FileWriter.h"
#include "SinglyLinkedList.h"
#include "SinglyLinkedListSort.h"
#include <string>
#include "ArraySort.h"
#include "DoublyLinkedListSort.h"
#include "Runner.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "DEBUG: Liczba argumentow (argc): " << argc << std::endl;
    for(int i=0; i<argc; ++i) {
        std::cout << "DEBUG: argv[" << i << "] = " << argv[i] << std::endl;
    }

    // Wywołanie czytania parametrów
    if (Parameters::readParameters(argc, argv) != 0) {
        std::cerr << "BLAD: Nie udalo sie wczytac parametrow!" << std::endl;
        return 1;
    }

    std::cout << "DEBUG: Tryb pracy: " << static_cast<int>(Parameters::runMode) << std::endl;

    Runner runner;
    runner.run();

    return 0;
}
