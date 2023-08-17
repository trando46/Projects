// Bao Tran Do
// File: MemberList.cpp
// September 28, 2020
// Purpose: This implementation is for the MemberList described MemberList.h

#include "MemberList.h"
#include <sstream>

int MemberList::memberCounter = 0;

MemberList::MemberList(int cap) {
    memberList = new memberStruct[cap];
    capacity = cap;
    numElements = 0;
}

MemberList::~MemberList() {
    delete [] memberList;
}

MemberList::MemberList(const MemberList &object) {
    // assign numElements and capacity (from obj)
    capacity = object.capacity;
    numElements = object.numElements;

    // allocate memory based on new capacity
    memberList = new memberStruct[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        memberList[i] = object.memberList[i];
}

void MemberList::addMember(string member) {
    if(numElements >= capacity){
        resizeMember();
    }
    memberList[numElements].member = member;
    memberList[numElements].memberID = numElements + 1;
    numElements++;
    memberCounter++;
}

string MemberList::get(int element) const {
    stringstream ss;
    for (int i = 0; i < numElements; i++) {
        if (memberList[i].memberID == element) {
             ss << memberList[i].member;
        }
    }
    return ss.str();
}

bool MemberList::empty() const{
    return numElements == 0;
}

int MemberList::sizeMember(){
    return memberCounter;
}

string MemberList::to_string() const {
    stringstream ss;
    for(int i = 0; i < numElements; i++){
        ss << memberList[i].memberID << ", " << memberList[i].member << endl;
    }
    return ss.str();
}

void MemberList::resizeMember() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    memberStruct * tempArr = new memberStruct[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = memberList[i];

    // delete old array
    delete [] memberList;

    // reassign old array to new array
    memberList = tempArr;
}