// Bao Tran Do
// File: BookList.cpp
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

string BookList::getBook(int element) const {
    stringstream ss;
    ss << bookList[element-1].ISBN << ", " << bookList[element-1].author << ", "
           << bookList[element-1].title << ", " << bookList[element-1].year;
    return ss.str();
}

bool BookList::empty() const {
    return numElements == 0;
}

int BookList::sizeBook(){
    return bookCounter;
}

string BookList::to_string() const {
    stringstream ss;
    for (int i = 0; i < numElements; i++)
        ss << bookList[i].ISBN << ", " << bookList[i].author
           << ", " << bookList[i].title << ", " << bookList[i].year << "\n";
    return ss.str();
}

string BookList::getMemberBooks(int memberID) const {
    stringstream ss;
    ss << bookList[memberID].ISBN << ", " << bookList[memberID].author << ", "
        << bookList[memberID].title << ", " << bookList[memberID].year;
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
