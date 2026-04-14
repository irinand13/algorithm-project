#include<iostream>

#include "ArraySort.h"
#include "FileReader.h"
#include "SinglyLinkedList.h"
#include "SinglyLinkedListSort.h"
#include "ArraySort.h"

using namespace std;

int main() {
     srand(time(nullptr));
     string fileName = "data.txt";
     Array<int> arr = readToArray<int>(fileName);
     Array<int> test = arr;
     test.read();
     cout << endl;
     cout << test.findMax() << endl;
     cout << test.findMin() << endl;
     int first = 0;
     int last = arr.getSize() - 1;
     Parameters::pivot = Parameters::Pivots::random;
     ArraySort::quickSort(test,first,last);
     test.read();
     ArraySort::bucketSort(test);
     test.read();



     // SinglyLinkedList<int> singlyLinkedList = readToSinlyLinkedList<int>(fileName);
     // singlyLinkedList.read();
     // cout << endl;
     // int max = singlyLinkedList.findMax();
     // int min = singlyLinkedList.findMin();
     //
     // SinglyLinkedListSort::bucketSort(singlyLinkedList, 10);
     // singlyLinkedList.read();
     // cout << max << endl;
     // cout << min << endl;



}