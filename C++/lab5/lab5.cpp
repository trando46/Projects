// Bao Tran Do
// File: lab5.cpp
// October 26, 2020
// Purpose: The purpose for this is to measure the runtimes of various sorting
//          algorithms using vectors
// INPUT: none
// OUTPUT: Display the measure runtimes for the various sorting algorithms

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Sort.h"
using namespace std;

int randomNumber(int min, int max);
// This function generates the random numbers between a min and max values
// IN: A value for min and a value for max
// MODIFY: none
// OUTPUT: none
void sortingValues(int size);
// This function takes in a size of the vector and display the measure runtimes
// for the various sorting algorithms such as merge, heap, quick, and introsort
// within that range
// IN: size of the vector
// MODIFY: none
// OUTPUT: none
void trials(int number);
// This function takes in a number to represent the trial number and calls
// the sortingValues function and the insertSort function
// IN: trial number
// MODIFY: none
// OUTPUT: none
void insertSort(int size);
// This function takes in a size of the vector and display the measure runtimes
// for the sorting algorithm for insertion sort within that range
// IN: size of the vector
// MODIFY: none
// OUTPUT: none

// Main application method
int main() {

    trials(1);
    trials(2);
    trials(3);

    return 0;
}

int randomNumber(int min, int max) {
    return rand() % max + min;
}

void sortingValues(int size){
    clock_t t;
    vector<long> vect(size);

    cout << "sorting " << size << " values...\n";

    ///QuickSort
    for (int i = 0; i < size; i++) {
        vect[i] = randomNumber(400000, 20480000);
    }
    t = clock();
    quicksort(vect.begin(), vect.end());
    t = clock() - t;
    cout << "It took me " << t << " clocks " << "(";
    printf("%.6f", (float) t/ 1000000);
    cout << ") seconds for QuickSort.\n";


    ///HeapSort
    for (int i = 0; i < size; i++) {
        vect[i] = randomNumber(400000, 20480000);
    }
    t = clock();
    heapsort(vect.begin(), vect.end());
    t = clock() - t;
    cout << "It took me " << t << " clocks " << "(";
    printf("%.6f", (float) t/ 1000000);
    cout << ") seconds for HeapSort.\n";

    ///MergeSort
    for (int i = 0; i < size; i++) {
        vect[i] = randomNumber(400000, 20480000);
    }
    t = clock();
    mergesort(vect.begin(), vect.end());
    t = clock() - t;
    cout << "It took me " << t << " clocks " << "(";
    printf("%.6f", (float) t/ 1000000);
    cout << ") seconds for MergeSort.\n";

    ///IntroSort(arrays.sort)
    for(int i = 0; i < size; i++) {
        vect[i] = randomNumber(400000, 20480000);
    }
    t = clock();
    sort(vect.begin(),vect.end());
    t = clock() - t;
    cout << "It took me " << t << " clocks " << "(";
    printf("%.6f", (float) t/ 1000000);
    cout << ") seconds for STL's IntroSort.\n";
    vect.clear();

}

void insertSort(int size){

    clock_t t;
    vector<long> vectInsert(size);

    ///InsertionSort
    for (int i = 0; i < size; i++) {
        vectInsert[i] = randomNumber(400000, 640000);
    }
    t = clock();
    insertionSort(vectInsert.begin(), vectInsert.end());
    t = clock() - t;
    cout << "It took me " << t << " clocks " << "(";
    printf("%.6f", (float) t/ 1000000);
    cout << ") seconds for InsertionSort.\n";
    cout << endl;
    vectInsert.clear();
}

void trials(int number){
    cout << "***************************\n";
    cout << "**        Trial   " << number << "      **\n";
    cout << "***************************\n";

    sortingValues(40000);
    insertSort(40000);
    sortingValues(80000);
    insertSort(80000);
    sortingValues(160000);
    insertSort(160000);
    sortingValues(320000);
    insertSort(320000);
    sortingValues(640000);
    insertSort(640000);

    sortingValues(1280000);
    cout << endl;
    sortingValues(2560000);
    cout << endl;
    sortingValues(5120000);
    cout << endl;
    sortingValues(10240000);
    cout << endl;
    sortingValues(20480000);
    cout << endl;
}


