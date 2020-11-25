// Bao Tran Do
// File: PatientPriorityQueue.h
// Specification file for the PatientPriorityQueue class used to create a vector
//      that stores the type Patient.

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H
#include "Patient.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

class PatientPriorityQueue {

public:

    PatientPriorityQueue();
    // Constructor that initializes the nextPatientNumber
    // precondition: nextPatientNumber is not initialize
    // postcondition: nextPatientNumber is initialize
    void add(Patient::Level, string);
    // This function add the patient to the priority queue and maintain the
    // heap order (the order that patients must be seen)
    // precondition: no patient is added
    // postcondition: there are now patients in the vector
    Patient remove();
    // This function removes the highest priority from the queue and returns
    // that patient from the queue. In addition, this function needs to
    // maintain heap order
    // precondition: the patient is still currently in the queue
    // postcondition: returns that patient is now removed from the queue
    Patient peek() const;
    // This function returns the highest priority patient without removing that
    // patient
    // precondition: none
    // postcondition: returns highest priority patient in the queue
    int size();
    // This function returns the number of patients still waiting
    // precondition: no patients are waiting
    // postcondition: returns the number of patients still waiting
    string to_string();
    // Returns the string representation of the object in heap (or level) order.
    // precondition: none
    // postcondition: returns the string representation

private:

    vector<Patient> data;       // Vector that takes in the type Patient
    int nextPatientNumber;      // Used to keep track of the last patient
                                //      inserted into the heap
    void heapifyUp(int);
    // This function performs a heapify up and organize patients in the
    // min heap order and a helper function for the add function
    // precondition: unsorted
    // postcondition: sorted
    void heapifyDown(int);
    // This functions performs a heapify down(swap until all the elements are
    // in sorted order) and a helper function for the remove function
    // precondition: all elements are present and insorted order
    // postcondition: an element is removed and perform in sorted order
    int getParent(int index) const;
    // Get the parent node position
    // precondition: none
    // postcondition: return the parent
    int getLeftChild(int index) const;
    // Get the left Child node position
    // precondition: none
    // postcondition: return the left Child
    int getRightChild(int index) const;
    // Get the right Child node position
    // precondition: none
    // postcondition: return the right Child
};

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 0;
}

int PatientPriorityQueue::size(){
    return data.size();
}

Patient PatientPriorityQueue::peek() const {
    assert(!(data.size() == 0));
    return data[0];
}

void PatientPriorityQueue::add(Patient::Level code, string name) {
    Patient member;
    member.setPriorityCode(code);
    member.setName(name);
    member.setArrival(nextPatientNumber + 1);
    data.push_back(member);
    heapifyUp(size() - 1);
    nextPatientNumber++;
}

Patient PatientPriorityQueue::remove() {
    assert(!(data.size() == 0));
    Patient temp = data[0];
    data[0] = data[size() - 1];
    data.pop_back();
    if (size() > 1){
        heapifyDown(0);
    }
    return temp;
}

string PatientPriorityQueue::to_string() {
    stringstream ss;
    for(int i = 0; i < size(); i++) {
        ss << data[i].to_string();
    }
    return ss.str();
}

//check if the this is in heap order (bottoms-up) when adding
void PatientPriorityQueue::heapifyUp(int index) {

    int parentIdx;
    Patient temp;
    if (index != 0) {
        parentIdx = getParent(index);
        if (data[parentIdx] < data[index]) {
            temp = data[parentIdx];
            data[parentIdx] = data[index];
            data[index] = temp;
            heapifyUp(parentIdx);
        }
    }
}

//do the shifting and swapping when the root is removed
void PatientPriorityQueue::heapifyDown(int index) {
    int leftIdx, rightIdx, maxIdx;
    Patient temp;
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // find minIdx
    if (rightIdx > size()) {
        if (leftIdx > size())
            return;
        else
            maxIdx = leftIdx;
    } else {
        if (data[leftIdx] > data[rightIdx])
            maxIdx = leftIdx;
        else
            maxIdx = rightIdx;
    }

    // swap?
    if (data[index] < data[maxIdx]) {
        temp = data[maxIdx];
        data[maxIdx] = data[index];
        data[index] = temp;
        heapifyDown(maxIdx);
    }
}

int PatientPriorityQueue::getParent(int index) const {
    return (index - 1) / 2;
}

int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}

#endif //P3_PATIENTPRIORITYQUEUE_H
