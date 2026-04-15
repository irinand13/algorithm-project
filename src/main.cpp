#include<iostream>

#include "ArraySort.h"
#include "FileReader.h"
#include "SinglyLinkedList.h"
#include "SinglyLinkedListSort.h"
#include "ArraySort.h"
#include "DoublyLinkedListSort.h"

using namespace std;

int main() {
     srand(time(nullptr));
     string fileName = "data.txt";
      Array<double> arr = readToArray<double>(fileName);
      Array<double> test = arr;

      if (test.isSorted()) {
           cout << "sorted" << endl;
      }else {
           cout << "not sorted" << endl;
      }

      test.read();
      cout << endl;
      Parameters::pivot = Parameters::Pivots::random;
      ArraySort::bucketSort(test);
      test.read();
      // ArraySort::bucketSort(test);
      // test.read();
      if (test.isSorted()) {
           cout << "sorted" << endl;
      }else {
           cout << "not sorted" << endl;
      }





     SinglyLinkedList<double> singlyLinkedList = readToSinlyLinkedList<double>(fileName);
     SinglyLinkedList<double> test1 = singlyLinkedList;
    Parameters::pivot = Parameters::Pivots::random;
    test1.read();
    if (test1.isSorted()) {
        cout << "sorted" << endl;
    }else {
        cout << "not sorted" << endl;
    }
     // SinglyLinkedListSort::bucketSort(test1);
     // test1.read();

     SinglyLinkedListSort::bucketSort(test1);
     test1.read();

    if (test1.isSorted()) {
        cout << "sorted" << endl;
    }else {
        cout << "not sorted" << endl;
    }

    DoublyLinkedList<double> doubly_linked = readToDoublyLinkedList<double>(fileName);
    DoublyLinkedList<double> test2 = doubly_linked;
    test2.read();
    if (test2.isSorted()) {
        cout << "Sorted" << endl;
    }else {
        cout << "Not Sorted" << endl;
    }
    Parameters::pivot = Parameters::Pivots::random;
    DoublyLinkedListSort::bucketSort(test2);
    test2.read();


    if (test2.isSorted()) {
        cout << "Sorted" << endl;
    }else {
        cout << "Not Sorted" << endl;
    }



}