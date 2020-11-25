// Bao Tran Do
// BookList.h
// September 22, 2020
// Specification file for the BookList class used to populate an array with
//    the book attributes: ISBN, author name, title of the book, and year.

#ifndef LAB2_BOOKLIST_H
#define LAB2_BOOKLIST_H
#include <string>
using namespace std;

class BookList {

private:

    struct bookStruct {
        int ISBN;
        string author, title, year;
    };                    // struct to hold different data types for the
                          // the book attributes.

    bookStruct * bookList;       // 1D dynamic array for the list of books
    int capacity;         // the array capacity
    int numElements;      // Number of elements in the array
    void resizeBook();    // Resize the array when it is full
    static int bookCounter;

public:

    BookList(int);
    // Constructor that takes in the argument int for capacity
    // precondition: the array size is empty
    // postcondition: the array size is set to a specific size

    ~BookList();
    // Destructor that deallocate the array (act as a garbage collector
    // precondition: an array that is allocated
    // post condition: deallocate the array

    BookList(const BookList & );
    // Copy the constructor
    // precondition: the allocate array is empty
    // postcondition: deep copy of the current array to the new allocate array

    void addBook(string,string,string);
    // add a book to the list of books
    // precondition: the array is empty
    // postcondition: each array index contains the ISBN, author, title, year

    int get(int) const;
    //find element in the array and return its index
    // precondition: none
    // postcondition: return the element in the array at that index.

    bool empty() const;
    // Determines if the list is empty or not
    // precondition: none
    // postcondition: list is empty

    static int size();
    // Determines the number of elements in array
    // preconditionL: the array is empty
    // postcondition: returns the total elements in the array

    string to_string() const;
    // Returns the string representation of the BookList class
    // precondition: none
    // postcondition: returns the string representation
};

#endif //LAB2_BOOKLIST_H
