// Bao Tran Do
// BookList.cpp
// September 22,2020
// Purpose: This implementation is for the BookList described in BookList.h

#include "BookList.h"
#include <sstream>

BookList::BookList(int cap)  {
    bookList = new bookStruct[cap];
    capacity = cap;
    numElements = 0;
}

int BookList::bookCounter = 0;

BookList::~BookList() {
    delete [] bookList;
}

BookList::BookList(const BookList &object) {
    // assign numElements and capacity (from obj)
    capacity = object.capacity;
    numElements = object.numElements;

    // allocate memory based on new capacity
    bookList = new bookStruct[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++)
        bookList[i] = object.bookList[i];
}

void BookList::addBook(string author, string title, string year) {
    if (numElements >= capacity)
        resizeBook();
    bookList[numElements].author = author;
    bookList[numElements].title = title;
    bookList[numElements].year = year;
    bookList[numElements].ISBN = numElements + 1;
    numElements++;
    bookCounter++;
}

int BookList::get(int element) const {
    for (int i = 0; i < numElements; i++) {
        if (bookList[i].ISBN == element)
            return i;
    }
    return -1;
}

bool BookList::empty() const {
    return numElements == 0;
}

int BookList::size(){
    return bookCounter;
}

string BookList::to_string() const {
    stringstream ss;
    for (int i = 0; i < numElements; i++)
        ss << bookList[i].ISBN << ", " << bookList[i].author
           << ", " << bookList[i].title << ", " << bookList[i].year << "\n";
    return ss.str();
}

void BookList::resizeBook() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    bookStruct * tempArr = new bookStruct[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++)
        tempArr[i] = bookList[i];

    // delete old array
    delete [] bookList;

    // reassign old array to new array
    bookList = tempArr;
}
