#include<iostream>

#include "ArraySort.h"
#include "FileReader.h"
#include "SinglyLinkedList.h"
#include "ArraySort.h"

using namespace std;

int main() {
     srand(time(NULL));
     string fileName = "data.txt";
     Array<int> arr = readToArray<int>(fileName);
     arr.read();
     cout << endl;
     cout << arr.findMax() << endl;
     cout << arr.findMin() << endl;
     int first = 0;
     int last = arr.getSize() - 1;
     ArraySort::quickSort(arr,first,last, PivotType::EXTREME);
     arr.read();


     //
     // SinglyLinkedList<int> singlyLinkedList = readToSinlyLinkedList<int>(fileName);
     // singlyLinkedList.read();
     // cout << endl;
     // int max = singlyLinkedList.findMax();
     // int min = singlyLinkedList.findMin();
     //
     // cout << max << endl;
     // cout << min << endl;



}