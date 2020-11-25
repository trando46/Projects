//
// Created by Bao Tran on 9/23/20.
//

#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H
#include <string>
using namespace std;


class RatingList {

public:

    RatingList(int);
    //Constructor that takes in the argument int for capacity
    // precondition: the array size is empty
    // postcondition: the array size is set to a specific size

    ~RatingList();
    // Destructor that deallocate the array(garbage collector)
    // precondition: an array that is allocated
    // post condition: deallocate the array

    RatingList(const RatingList &);
    // Create a deep copy
    // precondition: the allocate array is empty
    // postcondition: deep copy of the current array to the new allocate array

    void addRating(int,int,int);
    // Add the rating to the rating of books
    // precondition: the array is empty
    // postcondition: contains the ratings of each books for each members

    bool empty() const;
    // Determines if the list is empty or not
    // precondition: none
    // postcondition: list is empty

    static int sizeRating();
    // Determines the number of elements in array
    // preconditionL: the array is empty
    // postcondition: returns the total elements in the array

    string to_string() const;
    // Returns the string representation of the RatingList class
    // precondition: none
    // postcondition: returns the string representation

    int getMemberRating(int,int) const;
    // Returns the members' ratings(member is row; ratings is column).
    // precondition: none
    // postcondition: return the element in the array at that row and column.

    void addMemberRating(int,int,int);
    // Add that particular member's ratings to the books
    // precondition: the array is empty
    // postcondition: contains the ratings of each books for that member

private:

    static int booksCounter;    // Keep track of the members (column)
    static int memberCounter;              // Keep track of member (row)
    int numElements;              // Number of elements in the array
    int capacity;                 // The capacity of the array
    int ** ratingList;              // 1D dynamic array for the list of members
    void resizeRating();          // Resize the rating array when it is full

};

#endif //P1_RATINGLIST_H
