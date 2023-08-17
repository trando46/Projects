// Bao Tran Do
// File: MemberList.h
// September 28, 2020
// Specification file for the MemberList class used to populate an array with
//      members' name

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H
#include <string>
using namespace std;

class MemberList {

public:

    MemberList(int);
    //Constructor that takes in the argument int for capacity
    // precondition: the array size is empty
    // postcondition: the array size is set to a specific size

    ~MemberList();
    // Destructor that deallocate the array(garbage collector)
    // precondition: an array that is allocated
    // post condition: deallocate the array

    MemberList(const MemberList &);
    // Create a deep copy of the array
    // precondition: the allocate array is empty
    // postcondition: deep copy of the current array to the new allocate array

    void addMember(string);
    // Add the member to the member of books
    // precondition: the array is empty
    // postcondition: each index contains the members' name

    string get(int) const;
    // Fine element in the array and return its index
    // precondition: none
    // postcondition: return the element in the array at that index.

    bool empty() const;
    // Determines if the list is empty or not
    // precondition: none
    // postcondition: list is empty

    static int sizeMember();
    // Determines the number of elements in array
    // preconditionL: the array is empty
    // postcondition: returns the total elements in the array

    string to_string() const;
    // Returns the string representation of the MemberList class
    // precondition: none
    // postcondition: returns the string representation

private:
    struct memberStruct{
        string member;
        int memberID;
    };

    static int memberCounter;    // Keep track of the members
    int numElements;              // Number of elements in the array
    int capacity;                 // The capacity of the array
    memberStruct * memberList;    // 1D dynamic array for the list of members
    void resizeMember();          // Resize the member array when it is full

};


#endif //P1_MEMBERLIST_H
