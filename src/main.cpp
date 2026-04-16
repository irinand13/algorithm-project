#include<iostream>

#include "ArraySort.h"
#include "FileReader.h"
#include "DataGenerator.h"
#include "SinglyLinkedList.h"
#include "SinglyLinkedListSort.h"
#include <string>
#include "ArraySort.h"
#include "DoublyLinkedListSort.h"

using namespace std;

int main() {
     srand(time(nullptr));
     string fileName = "data.txt";
     auto arr = DataGenerator::generateArray<double>(10);

     for (int i = 0; i < 10; i++)std::cout << arr[i] << " ";

     std::cout << "\n";

     auto list = DataGenerator::generateSinglyLinkedList<char>(10);
     list.read();
     auto doubly_linked_list = DataGenerator::generateDoublyLinkedList<string>(10);
     doubly_linked_list.read();
}
