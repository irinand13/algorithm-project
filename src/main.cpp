#include<iostream>

#include "FileReader.h"
#include "SinglyLinkedList.h"
using namespace std;

int main() {
    string fileName = "data.txt";
    SinglyLinkedList<int> linked_list = readToSinlyLinkedList<int>(fileName);
    linked_list.read();
    linked_list.getSize();
}