// Bao Tran Do
// File: RatingList.cpp
// September 28, 2020
// Purpose: This implementation is for the RatingList described in RatingList.h

#include "RatingList.h"
#include <sstream>

int RatingList::booksCounter = 0;
int RatingList::memberCounter =0;

RatingList::RatingList(int cap) {
    ratingList = new int*[cap];
    //creating the rows
    for (int i = 0; i < cap; i++)
        ratingList[i] = new int[cap];
    capacity = cap;
    numElements = 0;
}

RatingList::~RatingList() {
    //deallocate memory for "members" & "ratings"
    for(int i = 0; i < capacity; i++) {
        delete[] ratingList[i];
    }
    delete [] ratingList;
}

RatingList::RatingList(const RatingList &object) {
    // assign numElements and capacity (from obj)
    capacity = object.capacity;
    numElements = object.numElements;

    // allocate memory based on new capacity
    ratingList = new int*[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        ratingList[i] = object.ratingList[i];
}

void RatingList::addRating(int accountNumber,int numberOfBooks, int readNumber) {

    if(numElements >= capacity){
        resizeRating();
    }

    ratingList[accountNumber][numberOfBooks] = readNumber;

    numElements++;
    booksCounter = numberOfBooks + 1;
    memberCounter = accountNumber + 1;

}

bool RatingList::empty() const {
    return numElements == 0;
}

int RatingList::sizeRating(){
    return booksCounter;
}

string RatingList::to_string() const {
    stringstream ss;
    for(int i = 0; i < memberCounter; i++){
        ss << i << " : ";
        for(int j = 0; j < booksCounter; j++){
            ss << ratingList[i][j]<< " ";
        }
        ss << endl;
    }
    return ss.str();
}

int RatingList::getMemberRating(int memberID,int colBook) const {
    return ratingList[memberID][colBook];
}

void RatingList::addMemberRating(int memberID, int ISBN, int readNumber) {
   ratingList[memberID-1][ISBN-1] = readNumber;

}

void RatingList::resizeRating() {

    //Declare the variable
    int oldCapacity;
    //store the size of the old capacity
    oldCapacity = capacity;

    capacity *= 2;

    int ** tempArr;

    //create dynamic array of new size
    tempArr = new int * [capacity];

    //create a 2d dynamic array
    for(int i = 0; i < capacity; i++){
        tempArr[i] = new int [capacity];
    }

    // move values from the old array to the new array with the current
    // row and col being smaller than incoming row and col
    if(oldCapacity <= capacity){
        //only loop through the old capacity if loop through the new one will
        //give an error cause there is no value that can be placed into the
        //the new one.
        for(int row = 0; row < oldCapacity; row++){
            for(int col = 0; col < oldCapacity; col++){
                tempArr[row][col] = ratingList[row][col];
            }
        }

        //Fill in the other empty cells with 0 or else it will give you a
        // different number
        for(int row = oldCapacity; row < capacity; row++){
            for(int col = oldCapacity; col < capacity; col++){
                tempArr[row][col] = 0;
            }
        }
    }

    //delete data
    for(int i = 0; i < oldCapacity; i++){
        delete [] ratingList[i];

    }

    // delete old array content
    delete [] ratingList;

    //Assign the old dynamic array to the new one
    ratingList = tempArr;
}