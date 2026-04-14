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
//      Array<int> arr = readToArray<int>(fileName);
//      Array<int> test = arr;
//
//      if (test.isSorted()) {
//           cout << "sorted" << endl;
//      }else {
//           cout << "not sorted" << endl;
//      }
//
//      test.read();
//      cout << endl;
//      Parameters::pivot = Parameters::Pivots::random;
//      ArraySort::shellSort(test);
//      test.read();
//      // ArraySort::bucketSort(test);
//      // test.read();
//      if (test.isSorted()) {
//           cout << "sorted" << endl;
//      }else {
//           cout << "not sorted" << endl;
//      }





     SinglyLinkedList<double> singlyLinkedList = readToSinlyLinkedList<double>(fileName);



     Parameters::pivot = Parameters::Pivots::random;
     SinglyLinkedList<double> test1 = singlyLinkedList;
    test1.read();
    if (test1.isSorted()) {
        cout << "sorted" << endl;
    }else {
        cout << "not sorted" << endl;
    }
     // SinglyLinkedListSort::bucketSort(test1);
     // test1.read();

     SinglyLinkedListSort::shellSort(test1);
     test1.read();

    if (test1.isSorted()) {
        cout << "sorted" << endl;
    }else {
        cout << "not sorted" << endl;
    }





}